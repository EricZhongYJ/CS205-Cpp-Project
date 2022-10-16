// There are two structs in this project.
#pragma once

// Integer struct
struct Integer
{
    // len, neg: The length and negative sign of the integer.
    // numInv: Record the unsigned integer by digit in inverse order
    int len;
    char neg, *numInv;

    // Constructor Function:
    // Vacant construction
    Integer();

    // Construction from certain length
    Integer(int len_, char neg_);

    // Construction for small integer
    Integer(int unint);

    // Construction from string
    Integer(char *str);

    // Transform Function:
    // Into string for output
    char const *to_string();

    // Into long long for using function
    long long to_longLong();

    // Compare Function:
    // To compare (with signed)
    bool cmp(Integer oth);

    // To compare absolutely
    char absCmp(Integer oth);

    // Calculate Function: (it will destroy the original object)
    // Add function
    Integer plus(Integer oth);

    // Subtract function
    Integer minus(Integer oth);

    // Product function
    Integer prod(Integer oth);

    // Shift or copy function
    // To shift by digit (n=0 & del=0 is to copy)
    Integer shift(int n, bool del);
};

// Number struct
struct Number
{
    // coeN: The coefficient of the float number (without dot)
    // expN: The exponent of the float number
    // A float number can be like: a.bc...*10^xyz...
    // then coeN = {abc...}, expN = {xyz...}.
    Integer coeN, expN;

    // Constructor Function:
    // Vacant construction for array initial
    Number();

    // Construction by variables
    Number(Integer coeN_, Integer expN_);

    // Construction from processed string
    Number(char *str, int dot, int e);

    // Construction from long double
    Number(long double num);

    // Copy function: construct a same Number
    Number copy();

    // Delete function:
    // Do not use destruct function because it will be done automaticly,
    // which is not expected.
    void del();

    // Transform Function:
    // Into string for output
    char const *to_string();

    // Into long double for using function
    long double to_longDouble();

    // Compare function: (with signed)
    char cmp(Number oth);

    // Calculate Function: (it will destroy the original object)
    // Add function
    Number plus(Number oth);

    // Subtract function
    Number minus(Number oth);

    // Product function
    Number prod(Number oth);

    // Divide function
    Number divide(Number oth);

    // To calculate the remainder (with signed)
    Number mod(Number oth);

    // Quick power for integer exponent
    Number powerI(long long expInt);

    // To round toward 0
    void fix();

    // Simplify function:
    // To clear zeros in the end of coefficient
    void clear0();
};