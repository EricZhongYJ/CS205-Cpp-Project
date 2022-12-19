// This file is to show the basic function of Class Matrix.
#include "Matrix.cpp"
using namespace std;

// To show Matrix or Expression
#define __SHOW_MAT(m) cout << "Mat " #m " is: " << m << endl;

int main(int argc, char const *argv[])
{
    // Basic function:
    // 1.Construction of Null Matrix, normal matrix, multi-channel matrix:
    cout << "===================== 1.Construction of Null Matrix, normal matrix, multi-channel matrix:" << endl;
    Matrix<int> a;
    __SHOW_MAT(a);
    Matrix b(2, 2, new double[]{1.1, 2.2, 3.3, 4.4});
    __SHOW_MAT(b);
    Matrix c(1, 4, new size_t[]{4, 3, 2, 1, 8, 7, 6, 5}, 2);
    __SHOW_MAT(c);
    // 2.All allowed types: bool, (unsigned) char, (unsigned) short,
    //                    (unsigned) int, (unsigned) long, (unsigned) long long,
    //                    float, double, long double.
    // 3.Copy
    cout << "===================== 3.Copy:" << endl;
    Matrix d = c;        // soft copy
    Matrix e(c);         // soft copy
    Matrix f = c.copy(); // hard copy
    d(0, 0) = 1000, e(0, 1) = 2000, f(0, 2) = 3000;
    __SHOW_MAT(c);
    Matrix g = c.sub(0, 1, 1, 3); // soft copy
    __SHOW_MAT(g);
    Matrix h = c.subCopy(0, 1, 1, 3); // hard copy
    g(0, 0, 1) = 4000, h(0, 1, 1) = 5000;
    __SHOW_MAT(c);
    // 4.Calculate
    cout << "===================== 4.Calculate:" << endl;
    Matrix i = Matrix<long>("[1,2;3,4]") + Matrix<long>("[10,20;30,40]");
    __SHOW_MAT(i);
    Matrix j = Matrix<long>("[1,2;3,4]") * Matrix<long>("[10,20;30,40]");
    __SHOW_MAT(j);
    // Mat: A/B = A * B.inv()
    Matrix k = Matrix<long double>("[1,2;3,4]") / Matrix<long>("[1,2;3,4]");
    __SHOW_MAT(k);
    // Mat: A^2 = A * A, B^-1 = B.inv(), C^0 = Id
    Matrix l = Matrix<short>("[1,2;3,4]") ^ 2;
    __SHOW_MAT(l);
    // ==, !=, <, >, <=, >=, return Matrix<bool>
    // Mat: A==A.transpose() -> Id or Ones
    __SHOW_MAT((l == l.transpose()));

    return 0;
}
