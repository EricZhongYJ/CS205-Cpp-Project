// This file is to implement a calculator.
// Author: 12012613 Zhong Yuanji钟元吉
// Encode: UTF-8
// Version: g++ (Ubuntu 11.2.0-19ubuntu1) 11.2.0
// Date: 2022/10/16
#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

// Include the head file
#include "../inc/StructHead.hpp"
#include "../inc/FunHead.hpp"
#include "../inc/GlobalVar.hpp"

int error[2];
// Functions, operators name and thier priority
const char *FUN_STR[] = {"floor", "ciel", "asin", "acos", "atan", "sqrt", "sin", "cos", "tan", "abs", "exp", "log"};
const char OP_SG[] = "()!^*/%+";
const int OP_PRIOR[] = {-1, 0, 4, 3, 2, 2, 2, 1};
// priority:   1:+-    2:*/%    3:^    4:!    5:function    6:()

// Variables about user's variables
int varId, numPt, opPt, eqId;
char *varName[100], *opSet, *priorSet;
Number varVal[100], *numSet;

// Analyse function for input string
void analyse(char *str)
{
    // Variables about input string
    int len = strlen(str), Id, lastId = 0;
    int dot = -1, e = -1;
    bool isNum = false, numEnd = false;
    // Variables about calculate stack
    numPt = -1, opPt = -1;
    numSet = new Number[len];
    opSet = new char[len];
    priorSet = new char[len];
    // Analyse every char of input
    for (Id = 0; Id < len && !error[0]; ++Id)
    {
        char now = str[Id];
        // It is not a number char
        if (now < '0' || now > '9')
        {
            bool cmp = false;
            // Compare to variables name
            for (int j = 0; j <= varId; ++j)
                if (strncasecmp(&(str[Id]), varName[j], strlen(varName[j])) == 0)
                {
                    addNumBVar;
                    numSet[++numPt] = varVal[j].copy();
                    Id += strlen(varName[j]) - 1;
                    goto NEXT_CHAR;
                }
            // Compare to functions name
            for (int j = 0; j < 12; ++j)
                if (strncasecmp(&(str[Id]), FUN_STR[j], strlen(FUN_STR[j])) == 0)
                {
                    addNumBVar;
                    isNum = false;
                    addOp(j, 5);
                    Id += strlen(FUN_STR[j]) - 1;
                    goto NEXT_CHAR;
                }
            // Compare to operators name
            for (int j = 0; j < 8 && !cmp; ++j)
                if (now == OP_SG[j])
                {
                    // '(' is special
                    if (now == '(')
                    {
                        addNumBVar;
                        isNum = false;
                    }
                    else
                    {
                        addNumBOp;
                        if (now == ')')
                            isNum = true, numEnd = true, str[Id] = ')';
                    }
                    addOp(now, OP_PRIOR[j]);
                    goto NEXT_CHAR;
                }
            // Compare to pi
            if ((now == 'p' || now == 'P') && (str[Id + 1] == 'i' || str[Id + 1] == 'I'))
            {
                addNumBVar;
                ++Id;
                numSet[++numPt] = constPi;
                goto NEXT_CHAR;
            }
            // Compare to 'e' / 'E'
            if (now == 'e' || now == 'E')
            {
                if (Id == 0 || str[Id - 1] == '\0' || str[Id - 1] == ')' || (str[Id + 1] != '-' && (str[Id + 1] < '0' || str[Id + 1] > '9')))
                {
                    addNumBVar;
                    numSet[++numPt] = constE;
                    str[Id] = '0';
                }
                else if (e >= 0)
                {
                    error[0] = 11, error[1] = Id;
                    return;
                }
                else
                    e = Id - lastId;
                goto NEXT_CHAR;
            } // Compare to '-'
            if (now == '-')
            {
                // As a minus signal
                if (Id != 0 && str[Id - 1] != '\0' && str[Id - 1] != 'e')
                {
                    addNumBOp;
                    addOp('-', 1);
                }
                // As an oppsite signal
                else if (!isNum)
                {
                    isNum = true, numEnd = false, lastId = Id;
                    dot = -1, e = -1;
                }
                goto NEXT_CHAR;
            } // Compare to '.'
            if (now == '.')
            {
                // Check if more than one dots or float exponent
                if (dot >= 0 || e >= 0)
                {
                    error[0] = 9 + (e >= 0), error[1] = Id;
                    return;
                }
                if (!isNum)
                    isNum = true, lastId = Id, e = -1;
                dot = Id - lastId;
                goto NEXT_CHAR;
            }
            // There is invalid char in the input
            error[0] = 4, error[1] = Id;
            return;
        NEXT_CHAR:
            continue;
        }
        // It is a number char
        else
        {
            // Last char is not number
            if (!isNum)
                lastId = Id, dot = -1, e = -1;
            else if (numEnd)
            {
                error[0] = 7, error[1] = Id;
                return;
            }
            isNum = true;
            numEnd = false;
        }
    }
    // Pick up the Number and finish the rest calculate in the end
    if (isNum && !numEnd)
        addstrNum(&(str[lastId]), dot, e);
    while (opPt >= 0 && priorSet[opPt] >= 0 && !error[0])
        calculate();
    // Save answer
    if (numPt == 0)
    {
        varVal[0].del();
        varVal[0] = numSet[numPt--];
    }
    else
        error[0] = 6;
    return;
}

// To sort Variable name by length from long to short
void sortVar()
{
    for (int i = 1; i < varId; ++i)
        for (int j = 1; j <= i; ++j)
            if (strlen(varName[j]) < strlen(varName[j + 1]))
            {
                char *tmp1 = varName[j];
                varName[j] = varName[j + 1];
                varName[j + 1] = tmp1;
                Number tmp2 = varVal[j];
                varVal[j] = varVal[j + 1];
                varVal[j + 1] = tmp2;
            }
}

// To calculate a single step
void calculate()
{
    // check error
    if (opPt < 0 || numPt < 0 || (numPt < 1 && opSet[opPt] > 12 && opSet[opPt] != '!'))
    {
        error[0] = 6;
        return;
    }
    Number tmp;
    long double value;
    long long valInt;
    switch (opSet[opPt])
    {
    case 0: // floor
        if (numSet[numPt].coeN.neg)
            numSet[numPt] = numSet[numPt].minus(Number(Integer(999999), Integer(-1)));
        numSet[numPt].fix();
        goto RET_CAL;
    case 1: // ciel
        if (!numSet[numPt].coeN.neg)
            numSet[numPt] = numSet[numPt].plus(Number(Integer(999999), Integer(-1)));
        numSet[numPt].fix();
        goto RET_CAL;
    case 2: // asin
        mathCal(asin);
    case 3: // acos
        mathCal(acos);
    case 4: // atan
        mathCal(atan);
    case 5: // sqrt
        mathCal(sqrt);
    case 6: // sin
        mathCal(sin);
    case 7: // cos
        mathCal(cos);
    case 8: // tan
        mathCal(tan);
    case 9: // abs
        numSet[numPt].coeN.neg = 0;
        goto RET_CAL;
    case 10: // exp
        mathCal(exp);
    case 11: // log
        mathCal(log);
    case '!': // factorial
        if (numSet[numPt].expN.to_longLong() > 7)
        { // answer will be to large
            error[0] = 13;
            return;
        }
        tmp = numSet[numPt].copy();
        tmp.coeN.neg = 0;
        tmp = tmp.minus(Number(Integer(1), Integer(0)));
        while (tmp.coeN.len > 0 && !tmp.coeN.neg)
        {
            numSet[numPt] = numSet[numPt].prod(tmp.copy());
            tmp = tmp.minus(Number(Integer(1), Integer(0)));
        }
        goto RET_CAL;
    case '^': // power
        value = numSet[numPt].to_longDouble();
        valInt = (long long)value;
        // Use quick power for integer
        if (valInt == value)
        {
            numSet[numPt - 1] = numSet[numPt - 1].powerI(valInt);
            numSet[numPt--].del();
        }
        else
        {
            tmp = numSet[numPt - 1];
            numSet[numPt - 1] = Number(pow(tmp.to_longDouble(), numSet[numPt].to_longDouble()));
            tmp.del(), numSet[numPt--].del();
        }
        goto RET_CAL;
    case '*':
        numSet[numPt] = numSet[--numPt].prod(numSet[numPt + 1]);
        goto RET_CAL;
    case '/':
        numSet[numPt] = numSet[--numPt].divide(numSet[numPt + 1]);
        goto RET_CAL;
    case '%':
        numSet[numPt] = numSet[--numPt].mod(numSet[numPt + 1]);
        goto RET_CAL;
    case '+':
        numSet[numPt] = numSet[--numPt].plus(numSet[numPt + 1]);
        goto RET_CAL;
    case '-':
        numSet[numPt] = numSet[--numPt].minus(numSet[numPt + 1]);
        goto RET_CAL;
    default:
        error[0] = 14;
        return;
    }
RET_CAL:
    --opPt;
    return;
}

// To add a Number from raw string to numberSet
void addstrNum(char *str, int dot, int e)
{
    if (e >= 0)
        str[e] = '\0';
    if (dot >= 0)
        for (int i = dot; str[i]; ++i)
            str[i] = str[i + 1];
    numSet[++numPt] = Number(str, dot, e);
}

// To an operator to operatorSet
void addOp(char op, int prior)
{
    if (op == ')')
    {
        while (priorSet[opPt] >= prior)
            if (opPt < 0)
            {
                error[0] = 5;
                return;
            }
            else
                calculate();
    }
    else if (opPt >= 0 && op != '(')
    {
        while (priorSet[opPt] >= prior && opPt >= 0)
            calculate();
    }
    if (error[0] || op == ')')
    {
        --opPt; // remove '('
        return;
    }
    opSet[++opPt] = op;
    priorSet[opPt] = prior;
}

// To asign a variable
void asignment(char *str)
{
    int len = (int)strlen(str);
    // Check if variable name is valid
    if (str[0] >= '0' && str[0] <= '9')
    {
        error[0] = 1, error[1] = 0;
        return;
    }
    for (int i = 0; i < len; ++i)
    {
        if (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= '0' && str[i] <= '9') || str[i] == '_'))
        {
            error[0] = 1, error[1] = i;
            return;
        }
    }
    // To check and cover the same name variable, i=0 is (default)"ans"
    for (int i = 1; i <= varId; ++i)
        if (!strcmp(varName[varId], str))
        {
            varVal[i].del();
            varVal[i] = varVal[0].copy();
            return;
        }
    // To do asignment
    varName[++varId] = new char[len];
    strcpy(varName[varId], str);
    varVal[varId] = varVal[0].copy();
    // To sort by length
    sortVar();
}

// Print what and where the error is
const char *WRONG_TAG[] = {
    "These are error type:",
    "The variable name on the left of equal sign is invalid",
    "There is no input",
    "The input cannot start with equal sign",
    "There is invalid char in the input",
    "The number of '(' and ')' are different",
    "The number of numbers or operators are wrong",
    "The numbers cannot follow a variable",
    "The operator cannot follow a operator",
    "There are more than one dots in a number",
    "The exponene cannot be a float",
    "There are more than one 'e' or 'E' in a number",
    "The divider cannot be zero",
    "There might be inf or nan in the expression",
    "There is an invalid operator in the input",
};
void printError(char *strCopy)
{
    if (error[0] != 1 && eqId)
        error[1] += eqId + 1;
    cout << strCopy << endl;
    // Show position
    if (error[0] != 9 && error[0] != 12)
    {
        for (int i = 0; i < error[1]; ++i)
            cout << " ";
        cout << "^~~~~~  (\"" << strCopy[error[1]] << "\" is invalid)\n";
    }
    cout << ((error[0] == 8 && error[1] == 0) ? "The input starts with a operator" : WRONG_TAG[error[0]])
         << ". Please try again."
         << endl;
}

// The main function
int main()
{
    // Initial and generate 'ans'
    char inpStr[5000];
    varId = 0;
    varName[0] = (char *)"ans";
    varVal[0] = Number(Integer(0), Integer(0));
    while (1)
    {
        eqId = 0, error[0] = 0, error[1] = 0;
        // Receive from input
        cout << "Please input the expression in the next line: (quit:q)" << endl;
        cin.getline(inpStr, 5000);
        if (strcmp(inpStr, "q") == 0)
            return 0;
        // Remove the blanks
        int orgLen = (int)strlen(inpStr);
        for (int i = 0, j = 0; j <= orgLen; ++j)
            if (inpStr[j] != ' ')
                inpStr[i++] = inpStr[j];
        // Check for null or equal at first char
        orgLen = strlen(inpStr);
        if (!orgLen || inpStr[0] == '=')
        {
            error[0] = 2 + bool(orgLen), error[1] = 0;
            printError(inpStr);
            continue;
        }
        // Copy for printing error
        char strCopy[orgLen + 1];
        strcpy(strCopy, inpStr);
        // Check if it is equality
        for (int i = 1; i < orgLen; ++i)
            if (inpStr[i] == '=' && inpStr[i - 1] != '<' && inpStr[i - 1] != '>' && inpStr[i + 1] != '=')
            {
                eqId = i;
                inpStr[eqId] = '\0';
                break;
            }

        // Analyse
        if (eqId)
        {
            analyse(&(inpStr[eqId + 1]));
            if (!error[0])
                asignment(inpStr);
        }
        else
            analyse(inpStr);
        // No error
        if (!error[0])
            cout << varVal[0].to_string() << endl;
        // Have some error
        else
            printError(strCopy);
        cout << endl;

        // free and delete
        for (int i = 0; i < numPt; ++i)
            numSet[i].del();
        delete[] numSet, delete[] opSet, delete[] priorSet;
    }
}
