// This is a head file of Matrix template class.
// Author: 12012613 Zhong Yuanji钟元吉
// Encode: UTF-8
// Version: gcc (Ubuntu 11.2.0-19ubuntu1) 11.2.0
// Version: gcc (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project) 12.2.0
// Date: 2022/12/18
#pragma once
#include <iostream>
// Matrix template class
template <typename _T>
class Matrix
{
    // Judge the type
    static_assert(
        std::is_same_v<_T, bool> ||
            std::is_same_v<_T, char> ||
            std::is_same_v<_T, unsigned char> ||
            std::is_same_v<_T, short> ||
            std::is_same_v<_T, unsigned short> ||
            std::is_same_v<_T, int> ||
            std::is_same_v<_T, unsigned int> ||
            std::is_same_v<_T, long> ||
            std::is_same_v<_T, unsigned long> ||
            std::is_same_v<_T, long long> ||
            std::is_same_v<_T, unsigned long long> ||
            std::is_same_v<_T, float> ||
            std::is_same_v<_T, double> ||
            std::is_same_v<_T, long double>,
        "The element type of Matrix must be Numberic. Matrix.hpp:8");
    // Datas
    static _T NULL_T;
    size_t row = 0, col = 0, lines = 0, channel = 0;
    int *ref = 0;
    _T *data = 0, *at = 0;

public:
    // Construction function
    Matrix();
    Matrix(size_t r, size_t c, _T *d, size_t cha = 1);
    Matrix(const char *strOrg);
    // Distruction function
    ~Matrix();
    void clear();

    // Tostring function
    char *tostring() const;
    // friend std::ostream &operator<<(std::ostream &os, const Matrix<_T> &m);

    // Copy function
    Matrix(const Matrix<_T> &oth);
    Matrix &operator=(const Matrix &oth);
    // Deep copy
    Matrix<_T> copy() const;
    // Copy from another type of Matrix (deep)
    template <typename __T>
    Matrix(const Matrix<__T> &oth);
    // Get value by index
    _T &operator()(size_t rowAt, size_t colAt, size_t chaAt = 0) const;
    // Get the size of Matrix
    size_t getRow() const;
    size_t getCol() const;
    size_t getChannel() const;
    Matrix<_T> getChannelMat(size_t chaAt = 0) const;
    // Get submatrix
    Matrix<_T> sub(size_t rowBegin, size_t rowEnd, size_t colBegin, size_t colEnd) const;
    Matrix<_T> subCopy(size_t rowBegin, size_t rowEnd, size_t colBegin, size_t colEnd) const;
    // Get cofactor matrix (deep)
    Matrix<_T> cofactorMatrix(size_t rowAt, size_t colAt) const;

    // All calculate function:
    // Compare function
    Matrix<bool> operator==(const Matrix &oth) const;
    Matrix<bool> operator!=(const Matrix &oth) const;
    Matrix<bool> operator<(const Matrix &oth) const;
    Matrix<bool> operator<=(const Matrix &oth) const;
    Matrix<bool> operator>(const Matrix &oth) const;
    Matrix<bool> operator>=(const Matrix &oth) const;
    // Addition
    Matrix<_T> operator+(_T num) const;
    Matrix<_T> operator+(const Matrix &oth) const;
    Matrix<_T> &operator+=(_T num);
    Matrix<_T> &operator+=(const Matrix &oth);
    // friend Matrix<_T> operator+(_T num, const Matrix<_T> &oth);
    // Substraction
    Matrix<_T> operator-(_T num) const;
    Matrix<_T> operator-(const Matrix &oth) const;
    Matrix<_T> &operator-=(_T num);
    Matrix<_T> &operator-=(const Matrix &oth);
    // friend Matrix<_T> operator-(_T num, const Matrix<_T> &oth);
    // Multiplication
    Matrix<_T> operator*(_T num) const;
    Matrix<_T> operator*(const Matrix &oth) const;
    Matrix<_T> &operator*=(_T num);
    Matrix<_T> &operator*=(const Matrix &oth);
    // friend Matrix<_T> operator*(_T num, const Matrix<_T> &oth);
    // Division
    Matrix<_T> operator/(_T num) const;
    Matrix<_T> operator/(const Matrix &oth) const;
    Matrix<_T> &operator/=(_T num);
    Matrix<_T> &operator/=(const Matrix &oth);
    // friend Matrix<_T> operator/(_T num, const Matrix &oth);
    // Power
    Matrix<_T> operator^(int num) const;
    // Find the minimal/Maximal values of a matrix
    _T min() const;
    _T max() const;
    // Compute the determinant
    long double det(size_t chaAt = 0) const;
    // Compute the inverse
    Matrix<long double> inv(size_t chaAt = 0) const;
    // Transpose the matrix
    Matrix<_T> transpose() const;
    // Rotate 90 degree on the matrix
    Matrix<_T> rotate90() const;
};

// Friend function head
template <typename _T>
std::ostream &operator<<(std::ostream &os, const Matrix<_T> &m);
template <typename _T>
Matrix<_T> operator+(_T num, const Matrix<_T> &oth);
template <typename _T>
Matrix<_T> operator-(_T num, const Matrix<_T> &oth);
template <typename _T>
Matrix<_T> operator*(_T num, const Matrix<_T> &oth);
template <typename _T>
Matrix<_T> operator/(_T num, const Matrix<_T> &oth);