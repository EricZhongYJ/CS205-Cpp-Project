#include <iostream>
// #include "../inc/Matrix.hpp"
#include "Matrix.cpp"
using namespace std;

int main(int argc, char const *argv[])
{
    Matrix<float> a = "[1,2,3 ;,4, 5,6 ; 7, 8 9e18]";
    // Matrix<int> a(3, 3, new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 60, 70, 80, 90}, 2);
    // auto size = a.getRow();
    a *= 2;
    cout << a << endl;
    return 0;
}
