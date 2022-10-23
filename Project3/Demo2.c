#include <stdio.h>
#include <stdlib.h>
#include "inc/Matrix.h"
// #include "src/MatrixFunc.c"
// Error tips
const char *ERR_STR[] = {"",
                         "Input Matrix mat is NULL pointer\n",
                         "Input Matrix oth is NULL pointer\n",
                         "Output Matrix ret is NULL pointer\n",
                         "The size of input Matrix is wrong\n",
                         "The input float row or col is wrong\n",
                         "The Matrix is not invertible\n"};
// Main method
main()
{
    Matrix *mat1 = createMatrixFromStr("[0]");
    Matrix *mat2 = createMatrix(1, 2, (__f *)malloc(2 * __SIZEF));
    Matrix *mat3 = NULLMatrix;
    Matrix *mat4 = NULL;
    int code = inv(mat4, mat2);
    printf(ERR_STR[-code]);
    code = addMatrix(mat1, mat4, mat2);
    printf(ERR_STR[-code]);
    code = subtractScalar(mat1, 2, mat4);
    printf(ERR_STR[-code]);
    code = multiplyMatrix(mat2, mat1, mat3);
    printf(ERR_STR[-code]);
    code = subMatrix(mat1, -1, 1, 0, 1, mat3);
    printf(ERR_STR[-code]);
    code = inv(mat1, mat2);
    printf(ERR_STR[-code]);
    return 0;
}