// This file is about the struct Matrix and function head
// Author: 12012613 Zhong Yuanji钟元吉
// Encode: UTF-8
// Version: gcc (Ubuntu 11.2.0-19ubuntu1) 11.2.0
// Version: gcc (MinGW.org GCC Build-2) 9.2.0
// Date: 2022/10/23
#ifndef __MATRIX_H__
#define __MATRIX_H__

// Define data type to store by float
// If you want to use double or long double, replace the float into them.
typedef float __f;
#define fFormat "%f"
#define NULLF 1.23456e11f // random number

// Define the size of float and Matrix
#define __SIZEF __SIZEOF_FLOAT__
#ifdef __WIN32
#define __SIZEM 12
#else
#define __SIZEM 16
#endif

// Matrix struct
struct Matrix
{
    int row, col;
    __f *data;
};
typedef struct Matrix Matrix;

// Functions:
// Return int:  1:sucessful
//             -1:input Matrix mat is NULL pointer
//             -2:input Matrix oth is NULL pointer
//             -3:output Matrix ret is NULL pointer
//             -4:the size of input Matrix is wrong
//             -5:the input float row or col is wrong
//             -6:the Matrix is not invertible
// Create a matrix from string or data
Matrix *createMatrix(int row_, int col_, __f *data_);
Matrix *createMatrixFromStr(const char *strOrg);

// Delete a matrix
int deleteMatrix(Matrix *mat);

// Transform a matrix to string
char *to_string(const Matrix *mat);

// Copy a matrix (copy the data from a matrix to another)
int copyMatrix(const Matrix *mat, Matrix *ret);
// Get submatrix (include ~Begin, not include ~End)
int subMatrix(const Matrix *mat, int rowBegin, int rowEnd, int colBegin, int colEnd, Matrix *ret);
// Get cofactor matrix
int cofactorMatrix(const Matrix *mat, int rowAt, int colAt, Matrix *ret);

// Compute
// Add two matrices
int addMatrix(const Matrix *mat, const Matrix *oth, Matrix *ret);
// Subtraction of two matrices
int subtractMatrix(const Matrix *mat, const Matrix *oth, Matrix *ret);
// Add a scalar to a matrix
int addScalar(const Matrix *mat, __f num, Matrix *ret);
// Subtract a scalar from a matrix
int subtractScalar(const Matrix *mat, __f num, Matrix *ret);
// Multiply a matrix with a scalar
int multiplyScalar(const Matrix *mat, __f num, Matrix *ret);
// Multiply two matrices
int multiplyMatrix(const Matrix *mat, const Matrix *oth, Matrix *ret);

// Find the minimal values of a matrix
__f minOfMatrix(const Matrix *mat);
// Find the maximal values of a matrix
__f maxOfMatrix(const Matrix *mat);

// Compute the determinant
__f det(const Matrix *mat);

// Compute the inverse
int inv(const Matrix *mat, Matrix *ret);

// Transpose the matrix
int transpose(const Matrix *mat, Matrix *ret);
// Rotate 90 degree on the matrix
int rotate90(const Matrix *mat, Matrix *ret);

// Create datas to store for change return matrix ret
#define __RetMat(_row, _col, _code)                         \
    int row = mat->row, col = mat->col;                     \
    if (!ret->data || ret->row != _row || ret->col != _col) \
    {                                                       \
        if (ret->data)                                      \
            free(ret->data);                                \
        ret->row = _row, ret->col = _col;                   \
        ret->data = (__f *)malloc((_row) * (_col)*__SIZEF);    \
    }                                                       \
    __f *data = mat->data, *data_ = ret->data;                \
    for (int i = 0; i < _row; ++i)                          \
        for (int j = 0; j < _col; ++j)                      \
        {                                                   \
            _code                                           \
        }

// Check if Matrix mat and ret are NULL pointer
#define __CheckMatRet \
    if (!mat)         \
        return -1;    \
    if (!ret)         \
        return -3;

// Define the NULL matrix
#define NULLMatrix createMatrix(0, 0, (__f *)malloc(__SIZEF))

#endif