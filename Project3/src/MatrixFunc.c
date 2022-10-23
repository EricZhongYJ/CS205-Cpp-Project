// This file is to implement the function of stuct Matrix.
// Author: 12012613 Zhong Yuanji钟元吉
// Encode: UTF-8
// Version: gcc (Ubuntu 11.2.0-19ubuntu1) 11.2.0
// Date: 2022/10/23
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/Matrix.h"

// Functions:
// Create a matrix from Data
Matrix *createMatrix(int row_, int col_, f *data_)
{
    // Check if the pointer is NULL, return 0x0 Matrix
    if (!data_)
        return NULLMatrix;
    Matrix *ret = (Matrix *)malloc(SIZE_M);
    ret->row = row_;
    ret->col = col_;
    ret->data = data_;
    return ret;
}

// Create a matrix from string
Matrix *createMatrixFromStr(const char *strOrg)
{
    if (!strOrg)
        return NULLMatrix;
    // Copy the string
    int orgLen = (int)strlen(strOrg);
    char *str = (char *)malloc(orgLen * sizeof(char));
    strcpy(str, strOrg);
    // Replace the blanks into ','
    for (int i = 0, j = 0; j <= orgLen; ++j)
        if (str[j] != ' ')
            str[i++] = str[j];
        else if (j != 0 && ((str[j - 1] >= '0' && str[j - 1] <= '9') || str[j - 1] == '.'))
            str[i++] = ',';
    int len = strlen(str);
    // Check format error
    if (len < 3 || str[0] != '[' || str[1] == ',' || str[1] == ';' || str[1] == ']' || str[len - 1] != ']')
        return NULLMatrix;
    while (str[len - 1] == ',' || str[len - 1] == ';' || str[len - 1] == ']')
        str[--len] = '\0';
    // Count rows and cols
    int countD = 0, countF = 0;
    for (int i = 1; i < len; ++i)
        if (str[i] == ';')
            ++countF;
        else if (str[i] == ',' && !countF)
            ++countD;
    // Read from string
    Matrix *ret = (Matrix *)malloc(SIZE_M);
    int At = 1;
    ret->row = countF + 1, ret->col = countD + 1;
    f *data_ = (f *)malloc((countF + 1) * (countD + 1) * SIZE_F);
    for (int i = 0; i <= countF; ++i)
        for (int j = 0; j <= countD; ++j, ++At)
        {
            sscanf(&str[At], fFormat, &data_[i * (countD + 1) + j]);
            for (; At < len; ++At)
            {
                if (str[At] == ',')
                {
                    if (str[At + 1] == ';')
                        ++At;
                    break;
                }
                else if (str[At] == ';')
                {
                    if (j != countD)
                        goto RETURN_NULL;
                    break;
                }
                else if ((str[At] < '0' || str[At] > '9') && str[At] != '.' && str[At] != '-' && str[At] != 'e' && str[At] != 'E')
                    goto RETURN_NULL;
            }
        }
    if (At < len)
        goto RETURN_NULL;
    free(str);
    ret->data = data_;
    return ret;
RETURN_NULL:
    free(str), free(ret), free(data_);
    return NULLMatrix;
}

// Delete a matrix
int deleteMatrix(Matrix *mat)
{
    if (!mat)
        return -1;
    if (mat->data)
        free(mat->data);
    free(mat);
    return 1;
}

// Transform a matrix to string
char *to_string(const Matrix *mat)
{
    if (!mat || mat->row == 0 || mat->col == 0)
        return (char *)"Matrix 0x0: []\n";
    int row = mat->row, col = mat->col;
    f *data = mat->data;
    char *ret = (char *)malloc((15 * row * col + row + 25) * sizeof(char));
    char *tmp = (char *)malloc(20 * sizeof(char));
    sprintf(ret, "Matrix %dx%d:\n[\n", row, col);
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            sprintf(tmp, "%15.6e", data[i * col + j]);
            strcat(ret, tmp);
        }
        strcat(ret, "\n");
    }
    strcat(ret, "]\n");
    free(tmp);
    return ret;
}

// Copy a matrix (copy the data from a matrix to another)
int copyMatrix(const Matrix *mat, Matrix *ret)
{
    __CheckMatRet;
    __RetMat(row, col, data_[i * col + j] = data[i * col + j];);
    return 1;
}

// Get submatrix (include ~Begin, not include ~End)
int subMatrix(const Matrix *mat, int rowBegin, int rowEnd, int colBegin, int colEnd, Matrix *ret)
{
    __CheckMatRet;
    // Check if 0 <= ~Begin < ~End <= mat.~
    if (0 > rowBegin || rowBegin >= rowEnd || rowEnd > mat->row ||
        0 > colBegin || colBegin >= colEnd || colEnd > mat->col)
        return -5;
    __RetMat(rowEnd - rowBegin, colEnd - colBegin,
             data_[i * (colEnd - colBegin) + j] = data[(rowBegin + i) * col + colBegin + j];);
    return 1;
}

// Get cofactor matrix
int cofactorMatrix(const Matrix *mat, int rowAt, int colAt, Matrix *ret)
{
    __CheckMatRet;
    // Check if 0 <= ~At < mat.~
    if (0 > rowAt || rowAt >= mat->row || 0 > colAt || colAt >= mat->col)
        return -5;
    __RetMat(row - 1, col - 1, data_[i * (col - 1) + j] = data[((i >= rowAt) ? (i + 1) : i) * col + ((j >= colAt) ? (j + 1) : j)];);
    return 1;
}

// Add two matrices
int addMatrix(const Matrix *mat, const Matrix *oth, Matrix *ret)
{
    if (!oth)
        return -2;
    __CheckMatRet;
    if (mat->row != oth->row || mat->col != oth->col)
        return -4;
    f *data2 = oth->data;
    __RetMat(row, col, data_[i * col + j] = data[i * col + j] + data2[i * col + j];);
    return 1;
}

// Subtraction of two matrices
int subtractMatrix(const Matrix *mat, const Matrix *oth, Matrix *ret)
{
    if (!oth)
        return -2;
    __CheckMatRet;
    if (mat->row != oth->row || mat->col != oth->col)
        return -4;
    f *data2 = oth->data;
    __RetMat(row, col, data_[i * col + j] = data[i * col + j] - data2[i * col + j];);
    return 1;
}

// Add a scalar to a matrix
int addScalar(const Matrix *mat, f num, Matrix *ret)
{
    __CheckMatRet;
    __RetMat(row, col, data_[i * col + j] = data[i * col + j] + num;);
    return 1;
}

// Subtract a scalar from a matrix
int subtractScalar(const Matrix *mat, f num, Matrix *ret)
{
    return addScalar(mat, -num, ret);
}

// Multiply a matrix with a scalar
int multiplyScalar(const Matrix *mat, f num, Matrix *ret)
{
    __CheckMatRet;
    __RetMat(row, col, data_[i * col + j] = data[i * col + j] * num;);
    return 1;
}

// Multiply two matrices
int multiplyMatrix(const Matrix *mat, const Matrix *oth, Matrix *ret)
{
    // Check and reset Matrix ret
    if (!oth)
        return -2;
    __CheckMatRet;
    if (mat->col != oth->row)
        return -4;
    int row = mat->row, col = mat->col, col2 = oth->col;
    f *data = mat->data, *data2 = oth->data;
    if (!ret->data || ret->row != row || ret->col != col2)
    {
        if (ret->data)
            free(ret->data);
        ret->row = row, ret->col = col2;
        ret->data = (f *)malloc(row * col2 * SIZE_F);
    }
    f *data_ = ret->data;
    // Initial and multiply by order j->k->i
    for (int i = 0; i < row * col2; i++)
        data_[i] = 0;
    for (int i = 0; i < row; ++i)
        for (int k = 0; k < col; ++k)
        {
            f num1 = data[i * col + k];
            for (int j = 0; j < col2; ++j)
                data_[i * col2 + j] += num1 * data2[k * (col2) + j];
        }
    return 1;
}

// Find the minimal values of a matrix
f minOfMatrix(const Matrix *mat)
{
    if (!mat || mat->row == 0 || mat->col == 0)
        return NULLF;
    int row = mat->row, col = mat->col;
    f *data = mat->data, ret = data[0];
    for (int i = 0; i < row * col; ++i)
        if (data[i] < ret)
            ret = data[i];
    return ret;
}

// Find the maximal values of a matrix
f maxOfMatrix(const Matrix *mat)
{
    if (!mat || mat->row == 0 || mat->col == 0)
        return NULLF;
    int row = mat->row, col = mat->col;
    f *data = mat->data, ret = data[0];
    for (int i = 0; i < row * col; ++i)
        if (data[i] > ret)
            ret = data[i];
    return ret;
}

// Compute the determinant of the matrix
f det(const Matrix *mat)
{
    if (!mat || mat->row == 0 || mat->col != mat->row)
        return NULLF;
    int row = mat->row, col = mat->col;
    f *data1 = mat->data, ret = 1;
    f *data = (f *)malloc(row * col * SIZE_F);
    for (int i = 0; i < row * col; ++i)
        data[i] = data1[i];
    for (int i = 0; i < row; ++i)
    {
        // Set M_i,i != 0
        for (int j = i; j < row; ++j)
            if (data[j * col + i] != 0)
            {
                if (i != j)
                {
                    for (int k = i; k < col; ++k)
                    {
                        f tmpF = data[i * col + k];
                        data[i * col + k] = data[j * col + k];
                        data[j * col + k] = tmpF;
                    }
                    if ((j - i) % 2)
                        ret *= -1;
                }
                break;
            }
        if (data[i * col + i] == 0)
            return 0;
        // Reduce by using Gauss Method
        ret *= data[i * col + i];
        for (int j = i + 1; j < row; ++j)
        {
            f num = data[j * col + i] / data[i * col + i];
            for (int k = i; k < col; ++k)
                data[j * col + k] -= num * data[i * col + k];
        }
    }
    free(data);
    return ret;
}

// Compute the inverse of the matrix
int inv(const Matrix *mat, Matrix *ret)
{
    __CheckMatRet;
    if (mat->row == 0 || mat->row != mat->col)
        return -4;
    f matDet = det(mat);
    if (matDet == 0)
        return -6;
    if (mat->row == 1)
    {
        if (!ret->data || ret->row != 1 || ret->col != 1)
        {
            if (ret->data)
                free(ret->data);
            ret->row = 1, ret->col = 1;
            ret->data = (f *)malloc(SIZE_F);
        }
        ret->data[0] = 1 / mat->data[0];
        return 1;
    }
    __RetMat(row, col,
             Matrix *tmp = NULLMatrix;
             cofactorMatrix(mat, j, i, tmp);
             data_[i * col + j] = ((i + j) % 2 ? -det(tmp) : det(tmp)) / matDet;
             deleteMatrix(tmp);
             ;);
    return 1;
}

// Transpose the matrix
int transpose(const Matrix *mat, Matrix *ret)
{
    __CheckMatRet;
    __RetMat(col, row, data_[i * row + j] = data[j * col + i];);
    return 1;
}

// Rotate 90 degree on the matrix
int rotate90(const Matrix *mat, Matrix *ret)
{
    __CheckMatRet;
    __RetMat(col, row, data_[i * row + j] = data[j * col + col - i - 1];);
    return 1;
}