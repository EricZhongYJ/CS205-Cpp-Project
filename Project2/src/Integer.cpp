// A struct of integer number of arbitrary number of digits
#include <string.h>
// Include the head file
#include "../inc/StructHead.hpp"
#include "../inc/GlobalVar.hpp"

// Integer struct:

// Vacant construction
Integer::Integer(){};
// Construction from certain length
Integer::Integer(int len_, char neg_)
{
    len = len_;
    neg = neg_;
    numInv = new char[len]();
}
// Construction for small integer
Integer::Integer(int unint)
{
    len = 0, neg = unint < 0;
    // For one digit integer
    if (unint < 10)
    {
        numInv = new char[1]{unint < 0 ? char(-unint) : char(unint)};
        if (unint) // not zero
            ++len;
        return;
    }
    numInv = new char[10];
    // Read digit by digit
    while (unint)
    {
        numInv[len++] = unint % 10;
        unint /= 10;
    }
}
// Construction from string
Integer::Integer(char *str)
{
    // Judge the negative signal
    neg = (str[0] == '-');
    len = strlen(str);
    // Read from str
    numInv = new char[len];
    int temp = len - 1;
    for (int i = temp; i >= 0; --i)
    {
        if (i == len - 1 && (str[temp - i] == '0' || str[temp - i] == '-'))
            --len;
        else
            numInv[i] = str[temp - i] - '0';
    }
}

// Into string for output
char const *Integer::to_string()
{
    if (len == 0)
        return "0";
    int strLen = len + neg;
    char *ret = new char[strLen + 1];
    for (int i = 0; i < len; ++i)
        ret[strLen - 1 - i] = numInv[i] + '0';
    ret[strLen] = '\0';
    if (neg)
        ret[0] = '-';
    return ret;
}
// Into long long for using function
long long Integer::to_longLong()
{
    long long ret = 0LL;
    for (int i = 0; i < len; ++i)
        ret = ret * 10 + numInv[len - 1 - i];
    if (neg)
        ret *= -1;
    return ret;
}

// To compare (with signed)
bool Integer::cmp(Integer oth)
{
    if (neg != oth.neg)
        return neg < oth.neg;
    return absCmp(oth) ^ neg; // equal return true
}
// To compare absolutely
char Integer::absCmp(Integer oth)
{
    if (len != oth.len)
        return len > oth.len;
    int diff = 0;
    for (int i = len - 1; i >= 0 && diff == 0; --i)
        diff = numInv[i] - oth.numInv[i];
    if (diff)
        return diff > 0;
    else
        return 2; // equal return 2
}

// To calculate (it will destroy the original object)
Integer Integer::plus(Integer oth)
{ // use minus to calculate plus
    oth.neg = 1 - oth.neg;
    return minus(oth);
}
Integer Integer::minus(Integer oth)
{
    bool retNeg = !cmp(oth);
    Integer ret = Integer(max(len, oth.len) + 1, retNeg);
    for (int i = 0; i < len; ++i)
        if (neg == retNeg)
            ret.numInv[i] = numInv[i];
        else
            ret.numInv[i] = -numInv[i];
    for (int i = 0; i < oth.len; ++i)
        if (oth.neg == retNeg)
            ret.numInv[i] -= oth.numInv[i];
        else
            ret.numInv[i] += oth.numInv[i];
    for (int i = 0; i < ret.len - 1; ++i)
        if (ret.numInv[i] < 0)
        {
            ret.numInv[i] += 10;
            --ret.numInv[i + 1];
        }
        else if (ret.numInv[i] > 9)
        {
            ret.numInv[i] -= 10;
            ++ret.numInv[i + 1];
        }
    for (int i = ret.len - 1; i >= 0; --i)
        if (ret.numInv[i])
            break;
        else
            --ret.len;
    delete[] numInv, delete[] oth.numInv;
    return ret;
}
Integer Integer::prod(Integer oth)
{
    Integer ret = Integer(len + oth.len + 1, neg ^ oth.neg);
    for (int i = 0; i < len; ++i)
        for (int j = 0; j < oth.len; ++j)
        {
            ret.numInv[i + j] += numInv[i] * oth.numInv[j];
            for (int id = i + j; id < ret.len - 1 && ret.numInv[id] > 9; ++id)
            {
                ret.numInv[id + 1] += ret.numInv[id] / 10;
                ret.numInv[id] %= 10;
            }
        }
    for (int i = ret.len - 1; i >= 0; --i)
        if (ret.numInv[i])
            break;
        else
            --ret.len;
    delete[] numInv, delete[] oth.numInv;
    return ret;
}

// To shift digit (n=0 & del=0 is to copy)
Integer Integer::shift(int n, bool del)
{
    Integer ret = Integer(len + n, neg);
    for (int i = max(0, -n); i < len; ++i)
        ret.numInv[i + n] = numInv[i];
    if (del)
        delete[] numInv;
    return ret;
}