// This file is to show the error checking function of Class Matrix.
#include "Matrix.cpp"
using namespace std;

// To show Matrix or Expression
#define __SHOW_MAT(m) cout << "Mat " #m " is: " << m << endl;

int main(int argc, char const *argv[])
{
    Matrix<int> numM = "[0]", vecM("[1,2,3]");
    // Error checking function:
    // 1.Unallowed type of Matrix
    /**   --All allowed types: bool, (unsigned) char, (unsigned) short,
     *                         (unsigned) int, (unsigned) long, (unsigned) long long,
     *                         float, double, long double.                            */
    cout << "===================== 1.Unallowed type of Matrix (it will cause a compile error)" << endl;
    // Matrix<cout> a; // compile error (with vscode tips)
    // Matrix<Matrix<int>> b; // compile error (with g++ tips)
    // Matrix<char32_t> b; // compile error (with g++ tips)
    // 2.Matrix is empty (with different tips)
    cout << "===================== 2.Matrix is empty (with different tips)" << endl;
    Matrix<int> emptyM = {1, 1, 0, 1}; // wrong then be setted as empty Matrix
    emptyM(0, 0);
    emptyM + 1; // same as +-*/^
    emptyM - numM;
    1 * emptyM;
    emptyM ^ 2;
    emptyM.det(); // same as most other functions(sub,cofactorMatrix,transpose,rotate90)
    emptyM.max(); // same as min()
    // 3.Initializing with invalid string
    cout << "===================== 3.Initializing with invalid string" << endl;
    Matrix<int> wrongM = "[1,2;3,4,5]"; // row != col
    // 4.The index was out of range of Matrix
    cout << "===================== 4.The index was out of range of Matrix" << endl;
    numM.getChannelMat(1);
    numM(1, 1);
    numM.sub(1, 2, 3, 4); // same as subCopy
    numM.cofactorMatrix(1, 1);
    // 5.The Begin index is bigger than End index
    cout << "===================== 5.The Begin index is bigger than End index" << endl;
    Matrix<int> rightM = "[1,2;3 4]";
    rightM.sub(1, 0, 1, 0); // same as subCopy
    // 6.The Matrices are in different size(or not square) when calculating
    cout << "===================== 6.The Matrices are in different size(or not square) when calculating" << endl;
    vecM + rightM;
    vecM.det();
    vecM.inv();
    // 7.The Matrix is not invertible
    cout << "===================== 7.The Matrix is not invertible" << endl;
    numM.inv();

    return 0;
}
