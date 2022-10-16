#pragma once

// To add a Number from raw string to numberSet
void addstrNum(char *str, int dot, int e);

// To an operator to operatorSet
void addOp(char op, int prior);

// Since it is pass variable and do asignment, use #define instead of function
// To add a Number before add an operator
#ifndef addNumBOp
#define addNumBOp                          \
    str[Id] = '\0';                        \
    if (isNum && !numEnd)                  \
    {                                      \
        addstrNum(&(str[lastId]), dot, e); \
        dot = -1, e = -1;                  \
    }                                      \
    else if (!isNum)                       \
    {                                      \
        error[0] = 8, error[1] = Id;       \
        return;                            \
    }                                      \
    isNum = false;
#endif

// To add a Number before add a variable
#ifndef addNumBVar
#define addNumBVar                             \
    str[Id] = '\0';                            \
    if (isNum)                                 \
    {                                          \
        if (!numEnd)                           \
        {                                      \
            addstrNum(&(str[lastId]), dot, e); \
            dot = -1, e = -1;                  \
        }                                      \
        addOp('*', 2);                         \
    }                                          \
    isNum = true,                              \
    numEnd = true;
#endif

// Definition of math calculate function
#ifndef mathCal
#define mathCal(__fun)                                  \
    tmp = numSet[numPt];                                \
    numSet[numPt] = Number(__fun(tmp.to_longDouble())); \
    tmp.del();                                          \
    goto RET_CAL
#endif

// Analyse function for input string
void analyse(char *str);

// To calculate a single step
void calculate();

// To asign a variable
void asignment(char *str);

// To sort user's Variable name by length from long to short
void sortVar();

// Print what and where the error is
void printError(char *strCopy);