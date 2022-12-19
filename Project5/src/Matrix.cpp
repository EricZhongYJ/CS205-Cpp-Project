// This is a function implement of Matrix template class.
// Author: 12012613 Zhong Yuanji钟元吉
// Encode: UTF-8
// Version: gcc (Ubuntu 11.2.0-19ubuntu1) 11.2.0
// Version: gcc (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project) 12.2.0
// Date: 2022/11/27
#include <string.h>
#include "../inc/Matrix.hpp"

// Template micro
#define _TP template <typename _T>
#define _MAT Matrix<_T>
// To print the error and its position
#define __PRINT_ERROR(tip) \
    std::cerr << "Error: " << (tip) << "\n\t" << __BASE_FILE__ << "\n\t" << __FILE__ << ":" << __LINE__ << " : " << __func__ << std::endl;
// To check if this is an empty Matrix
#define __CHECK_MAT(tip)                  \
    if (!row || !col || !channel || !ref) \
    {                                     \
        __PRINT_ERROR(tip);               \
        return _MAT();                    \
    }
#define __CHECK__T(tip)                   \
    if (!row || !col || !channel || !ref) \
    {                                     \
        __PRINT_ERROR(tip);               \
        return _T();                      \
    }

// Construction function
_TP _MAT::Matrix() {}
_TP _MAT::Matrix(size_t r, size_t c, const _T *d, size_t cha)
{
    if (r && c && cha && d)
    {
        row = r, col = c, lines = c, channel = cha;
        ref = new int(1);
        data = new _T[cha * r * lines], at = data;
        memcpy(data, d, cha * r * c * sizeof(_T));
    }
    else
        __PRINT_ERROR("The input row/col/channel are zero or data is empty when initializing a matrix.")
}
// Create a matrix from string
_TP _MAT::Matrix(const char *strOrg)
{
    if (!strOrg)
        return;
    // Copy the string
    size_t orgLen = strlen(strOrg);
    char str[orgLen];
    strcpy(str, strOrg);
    // Replace the blanks into ','
    for (size_t i = 0, j = 0; j <= orgLen; ++j)
        if ((str[j] == ',' || str[j] == ';') && str[i - 1] == ',')
            str[i - 1] = str[j];
        else if (str[j] != ' ')
            str[i++] = str[j];
        else if (j != 0 && ((str[j - 1] >= '0' && str[j - 1] <= '9') || str[j - 1] == '.'))
            str[i++] = ',';
    size_t len = strlen(str);
    // Check format error
    if (len < 3 || str[0] != '[' || str[1] == ',' || str[1] == ';' || str[1] == ']' || str[len - 1] != ']')
        return;
    while (str[len - 1] == ',' || str[len - 1] == ';' || str[len - 1] == ']')
        str[--len] = '\0';
    // Count rows and cols
    size_t countD = 0, countF = 0;
    for (size_t i = 1; i < len; ++i)
        if (str[i] == ';')
            ++countF;
        else if (str[i] == ',' && !countF)
            ++countD;
    // Read from string
    size_t At = 1;
    row = countF + 1, col = countD + 1;
    lines = col, channel = 1;
    ref = new int(1);
    data = new _T[row * col], at = data;
    for (size_t i = 0; i <= countF; ++i)
        for (size_t j = 0; j <= countD; ++j, ++At)
        {
            double temp;
            sscanf(&str[At], "%lf", &temp);
            at[i * lines + j] = (_T)temp;
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
                        goto RETURN_Error;
                    break;
                }
                else if ((str[At] < '0' || str[At] > '9') && str[At] != '.' && str[At] != '-' && str[At] != 'e' && str[At] != 'E')
                    goto RETURN_Error;
            }
        }
    if (At < len)
        goto RETURN_Error;
    return;
RETURN_Error:
    __PRINT_ERROR("The input string is not valid when initializing a matrix.");
    clear();
}
// Distruction function
_TP _MAT::~Matrix()
{
    clear();
}
_TP void _MAT::clear()
{
    row = 0, col = 0, lines = 0, channel = 0, at = 0;
    if (ref)
    {
        if (*ref == 1)
            delete ref, delete[] data, ref = 0, data = 0;
        else
            --*ref;
    }
}

// Tostring function
_TP char *_MAT::tostring() const
{
    if (!row || !col || !channel || !ref)
        return new char[]{"Matrix 0x0: []\n"};
    char *ret = new char[(15 * row * col + row + 35) * channel];
    ret[0] = '\0';
    char tmp[17];
    for (size_t k = 0; k < channel; ++k)
    {
        if (channel > 1)
        {
            sprintf(tmp, "Channel %ld:\n", k);
            strcat(ret, tmp);
        }
        sprintf(tmp, "Matrix %ldx%ld:\n[\n", row, col);
        strcat(ret, tmp);
        for (size_t i = 0; i < row; ++i)
        {
            for (size_t j = 0; j < col; ++j)
            {
                if (std::is_same_v<_T, float> || std::is_same_v<_T, double>)
                    sprintf(tmp, "%15.6f", at[(k * row + i) * lines + j]);
                else if (std::is_same_v<_T, long double>)
                    sprintf(tmp, "%15.6Lf", at[(k * row + i) * lines + j]);
                else
                    sprintf(tmp, "%15d", at[(k * row + i) * lines + j]);
                strcat(ret, tmp);
            }
            strcat(ret, "\n");
        }
        strcat(ret, "]\n");
    }
    return ret;
}
_TP std::ostream &operator<<(std::ostream &os, const _MAT &m)
{
    char *str = m.tostring();
    os << str;
    delete[] str;
    return os;
}

// Copy function
_TP _MAT::Matrix(const _MAT &oth)
{
    if (oth.row && oth.col && oth.channel && oth.ref)
        row = oth.row, col = oth.col, lines = oth.lines,
        channel = oth.channel, ref = oth.ref,
        data = oth.data, at = oth.at, *ref += 1;
}
_TP _MAT &_MAT::operator=(const _MAT &oth)
{
    clear();
    if (oth.row && oth.col && oth.channel && oth.ref)
        row = oth.row, col = oth.col, lines = oth.lines,
        channel = oth.channel, ref = oth.ref,
        data = oth.data, at = oth.at, *ref += 1;
    return *this;
}
// Deep copy
_TP _MAT _MAT::copy() const
{
    _MAT ret;
    if (row && col && channel && ref)
    {
        _T *data_ = new _T[channel * row * lines];
        memcpy(data_, data, row * lines * channel * sizeof(_T));
        ret.row = row, ret.col = col, ret.lines = lines;
        ret.channel = channel, ret.ref = new int(1);
        ret.data = data_;
        ret.at = size_t(at - data) + data_;
    }
    return ret;
}
// Copy as another type of Matrix (deep)
_TP template <typename __T>
Matrix<__T> _MAT::copyAs(__T eg) const
{
    _MAT ret;
    if (row && col && channel && ref)
    {
        __T *data_ = new __T[row * col];
        for (size_t i = 0; i < row * col; ++i)
            data_[i] = (__T)at[i];
        ret.row = row, ret.col = col, ret.lines = lines;
        ret.channel = channel, ret.ref = new int(1);
        ret.data = data_;
        ret.at = size_t(at - data) + data_;
    }
    return ret;
}

// Get the size of Matrix
_TP size_t _MAT::getRow() const { return row; };
_TP size_t _MAT::getCol() const { return col; };
_TP size_t _MAT::getChannel() const { return channel; };
_TP _MAT _MAT::getChannelMat(size_t chaAt) const
{
    if (chaAt >= channel)
    {
        __PRINT_ERROR("The index was out of range of Matrix when using 'getChannelMat()'.");
        return _MAT();
    }
    _MAT ret;
    ret.row = row, ret.col = col, ret.lines = lines;
    ret.ref = ref, ret.data = data;
    ret.at = at + chaAt * row * lines;
};
// Get value by index
_TP _T &_MAT::operator()(size_t rowAt, size_t colAt, size_t chaAt) const
{
    __CHECK_MAT("The fisrt Matrix is an empty Matrix when using 'operator()'.");
    if (rowAt >= row || colAt >= col)
    {
        __PRINT_ERROR("The index was out of range of Matrix when using 'operator()'.");
        return _T();
    }
    return at[(chaAt * row + rowAt) * lines + colAt];
}
// Get submatrix (do not copy)
_TP _MAT _MAT::sub(size_t rowBegin, size_t rowEnd, size_t colBegin, size_t colEnd) const
{
    __CHECK_MAT("The fisrt Matrix is an empty Matrix when using 'sub()'.");
    if (rowBegin >= row || rowEnd > row || colBegin >= col || colEnd > col)
    {
        __PRINT_ERROR("The index was out of range of Matrix when using 'sub()'.");
        return _MAT();
    }
    if (rowBegin >= rowEnd || colBegin >= colEnd)
    {
        __PRINT_ERROR("The Begin index is bigger than End index when using 'sub()'.");
        return _MAT();
    }
    _MAT ret;
    ret.row = rowEnd - rowBegin;
    ret.col = colEnd - colBegin;
    ret.lines = lines;
    ret.channel = channel;
    ret.ref = ref, ++*ref;
    ret.data = data;
    ret.at = at + (rowBegin * lines + colBegin);
    return ret;
}
// Get submatrix (do not copy)
_TP _MAT _MAT::subCopy(size_t rowBegin, size_t rowEnd, size_t colBegin, size_t colEnd) const
{
    __CHECK_MAT("The fisrt Matrix is an empty Matrix when using 'subCopy()'.");
    if (rowBegin >= row || rowEnd > row || colBegin >= col || colEnd > col)
    {
        __PRINT_ERROR("The index was out of range of Matrix when using 'subCopy()'.");
        return _MAT();
    }
    if (rowBegin >= rowEnd || colBegin >= colEnd)
    {
        __PRINT_ERROR("The Begin index is bigger than End index when using 'subCopy()'.");
        return _MAT();
    }
    _MAT ret;
    ret.row = rowEnd - rowBegin;
    size_t col_ = colEnd - colBegin;
    ret.col = col_, ret.lines = col_;
    ret.channel = channel, ret.ref = new int(1);
    ret.data = new _T[channel * ret.row * col_];
    ret.at = ret.data;
    for (size_t k = 0; k < channel; ++k)
        for (size_t i = 0; i < row; ++i)
            memcpy(ret.at + (k * row + i) * col_, at + ((k * row + rowBegin + i) * col + colBegin), col_ * sizeof(_T));
    return ret;
}
// Get cofactor matrix (deep)
_TP _MAT _MAT::cofactorMatrix(size_t rowAt, size_t colAt) const
{
    __CHECK_MAT("The fisrt Matrix is an empty Matrix when using 'cofactorMatrix()'.");
    if (rowAt >= row || colAt >= col)
    {
        __PRINT_ERROR("The index was out of range of Matrix when using 'cofactorMatrix()'.");
        return _MAT();
    }
    _MAT ret;
    ret.row = row - 1;
    size_t col_ = col - 1;
    ret.col = col_, ret.lines = col_;
    ret.channel = channel, ret.ref = new int(1);
    ret.data = new _T[channel * ret.row * col_];
    ret.at = ret.data;
    for (size_t k = 0; k < channel; ++k)
        for (size_t i = 0; i < col_; ++i)
        {
            memcpy(ret.at + (k * row + i) * col_, at + (k * row + i + (i >= rowAt)) * col, colAt * sizeof(_T));
            memcpy(ret.at + (k * row + i) * col_ + colAt, at + (k * row + i + (i >= rowAt)) * col + colAt + 1, col_ - colAt * sizeof(_T));
        }
    return ret;
}

// All calculate function:
// Compare function
#define __COMPARE_FUNCTION(signal)                                                            \
    _TP Matrix<bool> _MAT::operator signal(const Matrix &oth) const                           \
    {                                                                                         \
        if (row != oth.row || col != oth.col || channel != oth.channel ||                     \
            !row || !col || !channel || !ref ||                                               \
            !oth.row || !oth.col || !oth.channel || !oth.ref)                                 \
            return Matrix<bool>(1, 1, new bool((!row || !col) && (!oth.row || !oth.col)), 1); \
        bool *data_ = new bool[row * col * channel];                                          \
        for (size_t i = 0; i < row * channel; ++i)                                            \
            for (size_t j = 0; j < col; ++j)                                                  \
            {                                                                                 \
                data_[i * col + j] = at[i * lines + j] signal oth.at[i * oth.lines + j];      \
            }                                                                                 \
        return Matrix<bool>(row, col, data_, channel);                                        \
    }
__COMPARE_FUNCTION(==)
__COMPARE_FUNCTION(!=)
__COMPARE_FUNCTION(<)
__COMPARE_FUNCTION(<=)
__COMPARE_FUNCTION(>)
__COMPARE_FUNCTION(>=)
// Create a Matrix and return
#define __CREATE_RETURN(_row, _col, _cha, _code) \
    _T *data_ = new _T[_cha * _row * _col];      \
    _code;                                       \
    return _MAT(_row, _col, data_, _cha);
// Calculate function(+-)
#define __CALC_NUM(signal, name)                                                                                                                          \
    _TP _MAT _MAT::operator signal(_T num) const                                                                                                          \
    {                                                                                                                                                     \
        __CHECK_MAT("Empty Matrix cannot " #name " a number.")                                                                                            \
        __CREATE_RETURN(row, col, channel,                                                                                                                \
                        for (size_t i = 0; i < row * channel; ++i) for (size_t j = 0; j < col; ++j)                                                       \
                            data_[i * col + j] = at[i * lines + j] signal num;);                                                                          \
    }                                                                                                                                                     \
    _TP _MAT &_MAT::operator signal##=(_T num)                                                                                                            \
    {                                                                                                                                                     \
        _MAT temp = operator signal(num);                                                                                                                 \
        clear();                                                                                                                                          \
        *this = temp;                                                                                                                                     \
        return *this;                                                                                                                                     \
    }                                                                                                                                                     \
    _TP _MAT operator signal(_T num, const _MAT &oth)                                                                                                     \
    {                                                                                                                                                     \
        if (!oth.getRow() || !oth.getCol() || !oth.getChannel())                                                                                          \
        {                                                                                                                                                 \
            __PRINT_ERROR("Empty Matrix cannot " #name " a number.");                                                                                     \
            return _MAT();                                                                                                                                \
        }                                                                                                                                                 \
        __CREATE_RETURN(oth.getRow(), oth.getCol(), oth.getChannel(),                                                                                     \
                        for (size_t k = 0; k < oth.getChannel(); ++k) for (size_t i = 0; i < oth.getRow(); ++i) for (size_t j = 0; j < oth.getCol(); ++j) \
                            data_[(k * oth.getRow() + i) * oth.getCol() + j] = num signal oth(i, j, k););                                                 \
    }                                                                                                                                                     \
    _TP _MAT &_MAT::operator signal##=(const Matrix &oth)                                                                                                 \
    {                                                                                                                                                     \
        _MAT temp = operator signal(oth);                                                                                                                 \
        clear();                                                                                                                                          \
        *this = temp;                                                                                                                                     \
        return *this;                                                                                                                                     \
    }
#define __CALC_MAT(signal, name)                                                                       \
    _TP _MAT _MAT::operator signal(const _MAT &oth) const                                              \
    {                                                                                                  \
        __CHECK_MAT("Empty Matrix cannot " #name " a matrix.");                                        \
        if (!oth.row || !oth.col || !oth.channel || !oth.ref)                                          \
        {                                                                                              \
            __PRINT_ERROR("Empty Matrix cannot be " #name "ed.");                                      \
            return _MAT();                                                                             \
        }                                                                                              \
        else if (row != oth.row || col != oth.col || channel != oth.channel)                           \
        {                                                                                              \
            __PRINT_ERROR("Matrices of different size(or empty) cannot " #name " together.");          \
            return _MAT();                                                                             \
        }                                                                                              \
        __CREATE_RETURN(row, col, channel,                                                             \
                        for (size_t i = 0; i < row * channel; ++i) for (size_t j = 0; j < col; ++j)    \
                            data_[i * col + j] = at[i * lines + j] signal oth.at[i * oth.lines + j];); \
    }
__CALC_NUM(+, add)
__CALC_MAT(+, add)
__CALC_NUM(-, substract)
__CALC_MAT(-, substract)
__CALC_NUM(*, multiply)
__CALC_NUM(/, divide)
_TP _MAT _MAT::operator*(const Matrix &oth) const
{
    __CHECK_MAT("Empty Matrix cannot multiply a matrix.");
    if (!oth.row || !oth.col || !oth.channel || !oth.ref)
    {
        __PRINT_ERROR("Empty Matrix cannot be multiplied.");
        return _MAT();
    }
    else if (oth.row != col || channel != oth.channel)
    {
        __PRINT_ERROR("Matrices of different col and row cannot multiply together.");
        return _MAT();
    }
    // Use the Multiply with only storage access optimization to staisfy all data type
    _T *data_ = new _T[channel * row * col]();
    for (size_t n = 0; n < channel; ++n)
        for (size_t i = 0; i < row; ++i)
        {
            _T *num3 = data_ + ((n * oth.row + i) * oth.col);
            for (size_t k = 0; k < col; ++k)
            {
                _T num1 = at[(n * row + i) * lines + k],
                   *num2 = oth.at + (n * row + k) * lines;
                for (size_t j = 0; j < oth.col; ++j)
                    num3[j] += num1 * num2[j];
            }
        }
    return _MAT(row, col, data_, channel);
}
_TP _MAT _MAT::operator/(const Matrix &oth) const
{
    if (!row || !col || !channel || !ref || !oth.row || !oth.col || !oth.channel || !oth.ref)
    {
        __PRINT_ERROR("Empty Matrix cannot join division.");
        return _MAT();
    }
    else if (col != oth.row || col != oth.col)
    {
        __PRINT_ERROR("Matrices of different col and row cannot divide together.")
    }
    return operator*(oth.inv());
}
_TP _MAT _MAT::operator^(int num) const
{
    __CHECK_MAT("Empty Matrix cannot join power.");
    if (row != col)
    {
        __PRINT_ERROR("Only square Matrix can join power.");
        return _MAT();
    }
    if (num < 0)
        return inv() ^ (-num);
    _MAT Id;
    Id.row = row, Id.col = col, Id.lines = col;
    Id.ref = new int(1), Id.channel = channel;
    _T *data_ = new _T[channel * row * col]();
    for (size_t k = 0; k < channel; ++k)
        for (size_t i = 0; i < row; ++i)
            data_[(k * row + i) * col + i] = 1;
    Id.data = data_, Id.at = data_;
    if (num == 0)
        return Id;
    // Using fast power method
    _MAT temp = copy();
    while (num)
    {
        if (num % 2)
            Id *= temp;
        temp *= temp;
        num >>= 1;
    }
    return Id;
}
// Find the minimal/Maximal values of a matrix
_TP _T _MAT::min() const
{
    __CHECK__T("Empty Matrix have no minimial value.");
    _T ret = at[0];
    for (size_t i = 0; i < row * channel; ++i)
    {
        _T *temp = at + i * lines;
        for (size_t j = 0; j < col; ++j, ++temp)
            if (*temp < ret)
                ret = *temp;
    }
    return ret;
}
_TP _T _MAT::max() const
{
    __CHECK__T("Empty Matrix have no maximial value.");
    _T ret = at[0];
    for (size_t i = 0; i < row * channel; ++i)
    {
        _T *temp = at + i * lines;
        for (size_t j = 0; j < col; ++j, ++temp)
            if (*temp > ret)
                ret = *temp;
    }
    return ret;
}
// Compute the determinant
_TP long double _MAT::det(size_t chaAt) const
{
    // Check if it is empty
    if (!row || !col || !channel || !ref)
    {
        __PRINT_ERROR("Empty Matrix has no determinant.");
        return 0.L;
    }
    if (row != col)
        __PRINT_ERROR("Only square Matrix has determinant.");
    // Copy the data
    long double data_[row * col], ret = 0.L;
    for (size_t i = 0; i < row * col; ++i)
        data_[i] = (long double)at[i];
    // Eliminate for each row using Gauss Method
    for (size_t i = 0; i < row; ++i)
    {
        // Check M_{i,i} != 0, if not change the rows
        for (size_t j = i; j < row; ++j)
            if (data_[j * col + i] != 0)
            {
                if (i != j)
                { // Exchange two rows, determinant
                    for (size_t k = i; k < col; ++k)
                    {
                        long double tmp = data_[i * col + k];
                        data_[i * col + k] = data_[j * col + k];
                        data_[j * col + k] = tmp;
                    }
                    if ((j - i) % 2)
                        ret *= -1;
                }
                break;
            }
        // If no rows can make M_{i,i} != 0, the determinant is 0
        if (data_[i * col + i] == 0)
            return 0.L;
        // Eliminate by using Gauss Method
        ret *= data_[i * col + i];
        for (size_t j = i + 1; j < row; ++j)
        {
            long double num = data_[j * col + i] / data_[i * col + i];
            for (size_t k = i; k < col; ++k)
                data_[j * col + k] -= num * data_[i * col + k];
        }
    }
    return ret;
}
// Compute the inverse
_TP Matrix<long double> _MAT::inv(size_t chaAt) const
{
    // Check if it is empty
    if (!row || !col || !channel || !ref)
    {
        __PRINT_ERROR("Empty Matrix has no inverse.");
        return Matrix<long double>();
    }
    if (row != col)
    {
        __PRINT_ERROR("Only square Matrix has inverse.");
        return Matrix<long double>();
    }
    // If the size of matrix is 1x1
    if (row == 1)
    {
        long double ret = 1.L / at[chaAt * row * lines];
        return Matrix<long double>(1, 1, new long double[1]{ret}, 1);
    }
    long double *data_ = new long double[row * col], matDet = det();
    for (size_t i = 0; i < row; ++i)
        for (size_t j = 0; j < col; ++j)
        {
            Matrix tmp = cofactorMatrix(j, i);
            data_[i * col + j] = ((i + j) % 2 ? -det(tmp) : det(tmp)) / matDet;
        }
    return Matrix<long double>(row, col, data_, 1);
}
// Transpose the matrix
_TP _MAT _MAT::transpose() const
{
    __CHECK_MAT("Empty Matrix has no transpose.");
    long double *data_ = new long double[row * col], matDet = det();
    for (size_t i = 0; i < col; ++i)
        for (size_t j = 0; j < row; ++j)
            data_[i * row + j] = at[j * col + i];
    return Matrix<long double>(col, row, data_, 1);
}
// Rotate 90 degree on the matrix
_TP _MAT _MAT::rotate90() const
{
    __CHECK_MAT("Empty Matrix has no rotated Matrix.");
    long double *data_ = new long double[row * col], matDet = det();
    for (size_t i = 0; i < col; ++i)
        for (size_t j = 0; j < row; ++j)
            data_[i * row + j] = at[j * col + col - i - 1];
    return Matrix<long double>(col, row, data_, 1);
}

#undef _TP
#undef _MAT
#undef __PRINT_ERROR
#undef __CHECK_MAT
#undef __CHECK__T
#undef __COMPARE_FUNCTION
#undef __CREATE_RETURN
#undef __CALC_NUM
#undef __CALC_MAT