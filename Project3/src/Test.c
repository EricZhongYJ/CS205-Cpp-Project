// This file is a test of the matrix stuct.
// Author: 12012613 Zhong Yuanji钟元吉
// Encode: UTF-8
// Version: gcc (Ubuntu 11.2.0-19ubuntu1) 11.2.0
// Version: gcc (MinGW.org GCC Build-2) 9.2.0
// Date: 2022/10/24
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/Matrix.h"

// This file is to test and also an implement.
// Clear the bash under different operation system
#ifndef __linux
#define __CLEAR "cls"
#else
#define __CLEAR "clear"
#endif

// Choose a matrix by input
#define __Choose(str)                                                                   \
    printf("Please choose %s matrix:", str);                                            \
    printf("\n\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\tb(back)\n");                              \
    scanf("%s", input);                                                                 \
    while (input[1] != '\0' || (input[0] != 'b' && (input[0] < '0' || input[0] > '9'))) \
    {                                                                                   \
        printf("Please choose a matrix:\n");                                            \
        printf("\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\tb(back)\n");                            \
        scanf("%s", input);                                                             \
    }                                                                                   \
    if (input[0] == 'b')                                                                \
        goto START;

// Input a float
#define __InputF(str)                                                    \
    check = 1;                                                           \
    while (check)                                                        \
    {                                                                    \
        check = 0;                                                       \
        printf("Please input %s:\n", str);                               \
        scanf("%s", input);                                              \
        for (size_t i = 0; i < strlen(input); i++)                     \
            if ((input[i] < '0' || input[i] > '9') && input[i] != '.' && \
                input[i] != '-' && input[i] != 'e' && input[i] != 'E')   \
                check = 1;                                               \
    }

// Go back until input 'b'
#define __Back                                  \
    if (err < 0) /* Print the error */          \
    {                                           \
        printf("Error: %s", ERR_STR[-err]);     \
        err = 1;                                \
    }                                           \
    printf("Input 'b' to go back:\n");          \
    scanf("%s", input);                         \
    while (input[0] != 'b' || input[1] != '\0') \
    {                                           \
        printf("Input 'b' to go back:\n");      \
        scanf("%s", input);                     \
    }                                           \
    goto START;

// Get number from single function and go back
#define __GetNumBack(_fun)                  \
    __Choose("a");                          \
    id1 = input[0] - '0';                   \
    num1 = _fun(mats[id1]);                 \
    if (num1 == NULLF)                      \
        printf("Operation failed!\n");      \
    else                                    \
        printf("The answer is:%f\n", num1); \
    __Back

// Set the matrix from temp and go back
#define __SetMatBack(id)                             \
    if (temp->col == 0 || temp->row == 0 || err < 0) \
        printf("Operation failed!\n");               \
    else                                             \
    {                                                \
        printf("Operation sucessful!\n");            \
        copyMatrix(temp, mats[id]);                  \
    }                                                \
    __Back

// Show the result matrix temp and go back
#define __ShowMatBack                       \
    if (err < 0)                            \
    {                                       \
        printf("Operation failed!\n");      \
        __Back                              \
    }                                       \
    tempStr = to_string(temp);              \
    printf("The answer is: %s\n", tempStr); \
    free(tempStr);                          \
    printf("Choose a matrix to save:\n");   \
    __Choose("a target");                   \
    id1 = input[0] - '0';                   \
    __SetMatBack(id1)

// Get the matrix from single function, show the result matrix and go back
#define __GetMatBack(_fun)       \
    __Choose("a");               \
    id1 = input[0] - '0';        \
    err = _fun(mats[id1], temp); \
    __ShowMatBack

// Error tips
const char *ERR_STR[] = {"",
                         "Input Matrix mat is NULL pointer\n",
                         "Input Matrix oth is NULL pointer\n",
                         "Output Matrix ret is NULL pointer\n",
                         "The size of input Matrix is wrong\n",
                         "The input float row or col is wrong\n",
                         "The Matrix is not invertible\n"};

// main method
int main(int argc, char const *argv[])
{
    char input[1000];
    int id1, id2, err = 1;
    char check, *tempStr;
    __f num1, num2, num3, num4;
    Matrix *temp = NULLMatrix;
    Matrix *mats[10];
    for (int i = 0; i < 10; ++i)
        mats[i] = NULLMatrix;
    while (1)
    {
    START:
        system(__CLEAR);
        printf("Matrix Calculator:\n");
        printf("Operation:\n");
        printf("\t1:Define the matrix\t\t\t2:View the matrix\n");
        printf("\t3:Get the submatrix\t\t\t4:Get cofactor matrix\n");
        printf("\t5:Add two matrices\t\t\t6:Subtract two matrices\n");
        printf("\t7:Add matrix and scalar\t\t\t8:Subtract matrix and scalar\n");
        printf("\t9:Multiply two matrices\t\t\t10:Multiply matrix and scalar\n");
        printf("\t11:Get minimal of matrix\t\t12:Get maximal of matrix\n");
        printf("\t13:Get determinant of matrix\t\t14:Get inverse of matrix\n");
        printf("\t15:Transpose the matrix\t\t\t16:Rotate 90 degree on the matrix\n");
        printf("\tq:quit\n");
        scanf("%s", input);
        if (input[0] == '1')
            switch (input[1])
            {
            case '\0':
                __Choose("a");
                id1 = input[0] - '0';
                printf("Please input a matrix(using '[,;]'):\n");
                scanf("%s", input);
                temp = createMatrixFromStr(input);
                if (temp->col != 0 && temp->row != 0 && err > 0)
                {
                    tempStr = to_string(temp);
                    printf(tempStr);
                    if (temp->row != 0 && temp->col != 0)
                        free(tempStr);
                }
                __SetMatBack(id1);
            case '0':
                __Choose("a");
                id1 = input[0] - '0';
                __InputF("a number");
                sscanf(input, fFormat, &num1);
                err = multiplyScalar(mats[id1], num1, temp);
                __ShowMatBack;
            case '1':
                __GetNumBack(minOfMatrix);
            case '2':
                __GetNumBack(maxOfMatrix);
            case '3':
                __GetNumBack(det);
            case '4':
                __GetMatBack(inv);
            case '5':
                __GetMatBack(transpose);
            case '6':
                __GetMatBack(rotate90);
            }
        else if (input[1] == '\0')
            switch (input[0])
            {
            case 'q':
                return 0;
            case '2':
                __Choose("a");
                id1 = input[0] - '0';
                tempStr = to_string(mats[id1]);
                printf(tempStr);
                if (mats[id1]->row != 0 && mats[id1]->col != 0)
                    free(tempStr);
                __Back;
            case '3':
                __Choose("a");
                id1 = input[0] - '0';
                __InputF("the begin of row(include)");
                sscanf(input, fFormat, &num1);
                __InputF("the end of row(not include)");
                sscanf(input, fFormat, &num2);
                __InputF("the begin of col(include)");
                sscanf(input, fFormat, &num3);
                __InputF("the end of col(not include)");
                sscanf(input, fFormat, &num4);
                err = subMatrix(mats[id1], (size_t)num1, (size_t)num2, (size_t)num3, (size_t)num4, temp);
                __ShowMatBack;
            case '4':
                __Choose("a");
                id1 = input[0] - '0';
                __InputF("the row");
                sscanf(input, fFormat, &num1);
                __InputF("the col");
                sscanf(input, fFormat, &num2);
                err = cofactorMatrix(mats[id1], (size_t)num1, (size_t)num2, temp);
                __ShowMatBack;
            case '5':
                __Choose("the first");
                id1 = input[0] - '0';
                __Choose("the second");
                id2 = input[0] - '0';
                err = addMatrix(mats[id1], mats[id2], temp);
                __ShowMatBack;
            case '6':
                __Choose("the first");
                id1 = input[0] - '0';
                __Choose("the second");
                id2 = input[0] - '0';
                err = subtractMatrix(mats[id1], mats[id2], temp);
                __ShowMatBack;
            case '7':
                __Choose("a");
                id1 = input[0] - '0';
                __InputF("a number");
                sscanf(input, fFormat, &num1);
                err = addScalar(mats[id1], num1, temp);
                __ShowMatBack;
            case '8':
                __Choose("a");
                id1 = input[0] - '0';
                __InputF("a number");
                sscanf(input, fFormat, &num1);
                err = subtractScalar(mats[id1], num1, temp);
                __ShowMatBack;
            case '9':
                __Choose("the first");
                id1 = input[0] - '0';
                __Choose("the second");
                id2 = input[0] - '0';
                err = multiplyMatrix(mats[id1], mats[id2], temp);
                __ShowMatBack;
            }
    }
}
