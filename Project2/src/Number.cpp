// A struct of float number of arbitrary precision
#include <stdio.h>
#include <string.h>

// Include the head file
#include "../inc/StructHead.hpp"
#include "../inc/GlobalVar.hpp"

// Number struct:

// Vacant construction for array initial
Number::Number() {}
// Construction
Number::Number(Integer coeN_, Integer expN_)
{
    coeN = coeN_;
    expN = expN_;
}
// Construction from processed string
Number::Number(char *str, int dot, int e)
{ // e->'\0', dot:remove & left shift
    coeN = Integer(str);
    if (e >= 0)
        expN = Integer(&(str[e + 1]));
    else
    {
        expN = Integer(0);
        e = strlen(str) + 1;
    }
    expN = expN.plus(Integer((dot >= 0 ? dot - e : -1) + coeN.len));
    clear0();
}
// Construction from long double
Number::Number(long double num)
{
    char str[30];
    sprintf(str, "%.19Le", num);
    int dot = -1, e = -1, len = (int)strlen(str);
    // Check if num is inf or nan, return 0
    if (str[len - 1] == 'f' || str[len - 1] == 'n' || str[3] == '#')
    {
        error[0] = 13;
        coeN = Integer(0), expN = Integer(0);
        return;
    }
    // prograss: raw string -> processed string
    for (int i = 0; i < len; i++)
    {
        if (str[i] == 'e')
        {
            if (str[i + 1] == '+')
                e = i + 1, str[i + 1] = '\0';
            else
                e = i;
            str[i] = '\0';
        }
        if (dot >= 0 && e < 0)
            str[i - 1] = str[i];
        if (str[i] == '.')
        {
            dot = i;
            str[i] = str[i + 1];
        }
    }
    if (e)
        str[e - 1] = '\0';
    // using construction from processed string
    Number ret = Number(str, dot, e);
    coeN = ret.coeN, expN = ret.expN;
}
// Construct a same Number
Number Number::copy()
{
    return Number(coeN.shift(0, 0), expN.shift(0, 0));
}

// To delete
void Number::del()
{
    delete[] coeN.numInv, delete[] expN.numInv;
}

// Into string for output
char const *Number::to_string()
{
    // check if it is 0
    if (coeN.len == 0)
        return "0";
    // initial
    int strLen = coeN.len + coeN.neg + (coeN.len != 1);
    char *ret = new char[strLen + 2 + expN.len];
    for (int i = 0; i < coeN.len; ++i)
        ret[strLen - 1 - i] = coeN.numInv[i] + '0';
    if (coeN.neg)
        ret[0] = '-';
    if (coeN.len != 1)
    {
        ret[0 + coeN.neg] = ret[1 + coeN.neg];
        ret[1 + coeN.neg] = '.';
    }
    if (expN.len)
    {
        ret[strLen] = 'e';
        ret[strLen + 1] = '\0';
        strcat(ret, expN.to_string());
    }
    else
        ret[strLen] = '\0';
    return ret;
}
// Into long double for using function
long double Number::to_longDouble()
{
    long double ret;
    sscanf(to_string(), "%Lf", &ret);
    return ret;
}

// To compare (with signed)
char Number::cmp(Number oth)
{
    // one is 0
    if (coeN.len == 0)
        return oth.coeN.neg;
    if (oth.coeN.len == 0)
        return !coeN.neg;
    // different signed
    if (coeN.neg != oth.coeN.neg)
        return coeN.neg < oth.coeN.neg;
    // different exponent
    long long diffE = expN.to_longLong() - oth.expN.to_longLong();
    if (diffE)
        return (diffE > 0) ^ coeN.neg;
    // shift to compare digit
    Integer tmp;
    int diff = coeN.len - oth.coeN.len;
    char ret;
    if (diff > 0)
    {
        tmp = oth.coeN.shift(diff, 0);
        ret = coeN.absCmp(tmp) ^ coeN.neg;
    }
    else
    {
        tmp = coeN.shift(-diff, 0);
        ret = tmp.absCmp(oth.coeN) ^ coeN.neg;
    }
    delete[] tmp.numInv;
    return ret; // equal return 2 or 3
}

// To calculate (it will destroy the original object)
Number Number::plus(Number oth)
{
    oth.coeN.neg = 1 - oth.coeN.neg;
    return minus(oth);
}
Number Number::minus(Number oth)
{
    Number ret;
    int shiftN = oth.coeN.len - coeN.len + int(expN.to_longLong() - oth.expN.to_longLong());
    if (shiftN > 0) // this need to add digit 0 at the end
    {
        ret = Number(coeN.shift(shiftN, false).minus(oth.coeN), expN);
        ret.expN = ret.expN.minus(Integer(coeN.len - ret.coeN.len + shiftN));
        delete[] oth.expN.numInv, delete[] coeN.numInv;
    }
    else // oth need to add digit 0 at the end
    {
        ret = Number(coeN.minus(oth.coeN.shift(-shiftN, false)), expN);
        ret.expN = ret.expN.minus(Integer(coeN.len - ret.coeN.len));
        oth.del();
    }
    ret.clear0();
    return ret;
}
Number Number::prod(Number oth)
{
    Number ret = Number(coeN.prod(oth.coeN), expN.plus(oth.expN));
    ret.expN = ret.expN.plus(Integer(ret.coeN.len - coeN.len - oth.coeN.len + 1));
    ret.clear0();
    return ret;
}
Number Number::divide(Number oth)
{
    // Check if divide by zero
    if (oth.coeN.len == 0)
    {
        error[0] = 12;
        return oth;
    }
    // Calculate only 200 digit (because some fraction has infinite digit like 1/3)
    Integer num1 = coeN.shift(400 - coeN.len, true);
    Integer num2 = oth.coeN.shift(400 - oth.coeN.len, true);
    num1.neg = 0, num2.neg = 0;
    char cmp = num1.absCmp(num2);
    if (cmp == 2) // num1 == num2
    {
        delete[] num1.numInv, delete[] num2.numInv;
        return Number(Integer(coeN.neg ^ oth.coeN.neg ? -1 : 1), expN.minus(oth.expN));
    }
    else if (!cmp) // num1 < num2, expN--
    {
        expN = expN.minus(Integer(1));
        for (int i = 0; i < 399; i++)
            num2.numInv[i] = num2.numInv[i + 1];
        --num2.len;
    }
    Number ret = Number(Integer(200, coeN.neg ^ oth.coeN.neg), expN.minus(oth.expN));
    // calculate digit by digit
    for (int i = 0; i < 200; ++i)
        for (char k = 0; k < 10; ++k)
        {
            cmp = num1.absCmp(num2);
            if (cmp == 2) // num1 - k * num2 == num2, record and return
            {
                ret.coeN.numInv[199 - i] = k + 1;
                goto RETURN;
            }
            else if (!cmp) // num1 - k * num2 < num2, break and record
            {
                ret.coeN.numInv[199 - i] = k;
                for (int i = 0; i < 399; i++)
                    num2.numInv[i] = num2.numInv[i + 1];
                --num2.len;
                break;
            }
            else // num1 - k * num2 > num2, minus
                num1 = num1.minus(num2.shift(0, 0));
        }
RETURN: // use goto instead of break twice
    delete[] num1.numInv, delete[] num2.numInv;
    ret.clear0();
    return ret;
}
// To calculate the remainder (with signed)
Number Number::mod(Number oth)
{
    Number quo = copy().divide(oth.copy());
    quo.fix();
    return minus(quo.prod(oth));
}
// quick power for integer exponent
Number Number::powerI(long long expInt)
{
    Number ret = Number(Integer(1), Integer(0));
    Number under = *this;
    while (expInt)
    {
        if (expInt % 2)
            ret = ret.prod(under.copy());
        under = under.prod(under.copy());
        if (under.coeN.len > 1500)
            under.coeN = under.coeN.shift(1500 - under.coeN.len, 1);
        if (ret.coeN.len > 1500)
            ret.coeN = ret.coeN.shift(1500 - ret.coeN.len, 1);
        expInt >>= 1;
    }
    under.del();
    return ret;
}
// To round toward 0
void Number::fix()
{
    // |this| < 1
    int exp = int(expN.to_longLong());
    if (exp < -1)
    {
        coeN.len = 0;
        return;
    }
    // |this| > 1
    int shiftN = coeN.len - exp - 1;
    if (shiftN > 0)
        coeN = coeN.shift(-shiftN, 1);
}

// To clear zeros in the end of coefficient
void Number::clear0()
{
    int i, len = coeN.len;
    if (!len)
        expN.len = 0;
    for (i = 0; coeN.numInv[i] == 0 && i < len; ++i)
        --coeN.len;
    if (i)
        for (int k = 0; k < coeN.len; ++k)
            coeN.numInv[k] = coeN.numInv[k + i];
}
