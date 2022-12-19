// This file is to show the special function of Class Matrix.
#include "Matrix.cpp"
using namespace std;

// To show Matrix or Expression
#define __SHOW_MAT(m) cout << "Mat " #m " is: " << m << endl;

int main(int argc, char const *argv[])
{
    // Special function:
    // 1.Constract Matrix by string: (smartly recognize blanks)
    Matrix<int> a("[1,2,3;4,5,5;7,8,8]");
    __SHOW_MAT(a);
    Matrix<int> b = "[1,2 3; 4, 5 ,6]";
    __SHOW_MAT(b);
    Matrix c = Matrix<float>("[1   2.2 -3.1  ;  3e4  5e-2 -1e-4 ]");
    __SHOW_MAT(c);
    // 2.Automatically transform into different class of Matrix<_T>
    // tips: when using operators,the form will decide by the first Matrix
    __SHOW_MAT(b + c);
    __SHOW_MAT(c + b);
    __SHOW_MAT((Matrix<bool>)c - b); // c->Matrix<bool>, b->Matrix<bool>, c-b
    // 3.Getter function to protect the private variables
    cout << "size of a: " << a.getRow() << " x " << a.getCol() << " x " << a.getChannel() << endl;
    // 4.Other special function
    cout << "===============================================================" << endl;
    __SHOW_MAT(a.cofactorMatrix(0, 0))   // Return new Matrix deleting specified row and column
    __SHOW_MAT(a.getChannelMat(0))       // Return specified channel (no data copy)
    __SHOW_MAT(((Matrix<double>)a ^ -3)) // = a.inv() * a.inv() * a.inv(), using fast power
    __SHOW_MAT(a.det())                  // Determinant
    __SHOW_MAT(a.inv())                  // Inverse (return Matrix<long double>)
    __SHOW_MAT(a.inv() * a)
    __SHOW_MAT(a.transpose())
    __SHOW_MAT(a.rotate90())
    a.clear(); // Into empty Matrix and free the data safely (if it's only reference)

    return 0;
}
