#include <stdio.h>
#include <stdlib.h>
#include "inc/Matrix.h"
// #include "src/MatrixFunc.c"
// For output
#define __show(n, mat)             \
    temp = to_string(mat);         \
    printf("mat%d = %s", n, temp); \
    if (mat->row && mat->col)      \
        free(temp);
// Main method
int main()
{
    char *temp; // For freeing
    Matrix *mat1 = NULLMatrix;
    __show(1, mat1);
    Matrix *mat2 = createMatrix(1, 2, (__f *)malloc(2 * __SIZEF));
    __show(2, mat2);
    Matrix *mat3 = createMatrixFromStr("[1, 2;3 4; ]");
    __show(3, mat3);
    printf("=======================================\n");
    copyMatrix(mat3, mat1);
    __show(1, mat1);
    deleteMatrix(mat3);
    mat3 = createMatrixFromStr("[1,2,3;4,5,6;7,8,9]");
    __show(3, mat3);
    subMatrix(mat3, 1, 3, 1, 3, mat2);
    __show(2, mat2);
    cofactorMatrix(mat3, 1, 1, mat1);
    __show(1, mat1);
    printf("=======================================\n");
    // mat1 = [1,3;7,9], mat2 = [5,6;8,9];
    addMatrix(mat1, mat2, mat3);
    __show(3, mat3);
    subtractMatrix(mat1, mat2, mat3);
    __show(3, mat3);
    addScalar(mat2, 0.1, mat3);
    __show(3, mat3);
    subtractScalar(mat2, 0.1, mat3);
    __show(3, mat3);
    multiplyMatrix(mat1, mat2, mat3);
    __show(3, mat3);
    multiplyScalar(mat2, 0.5, mat3);
    __show(3, mat3);
    printf("=======================================\n");
    // mat1 = [1,3;7,9], mat2 = [5,6;8,9];
    printf("determinant of mat1 = %f\n", det(mat1));
    printf("determinant of mat2 = %f\ninverse of mat1 = ", det(mat2));
    inv(mat1, mat3);
    __show(3, mat3);
    multiplyMatrix(mat1, mat3, mat2);
    __show(2, mat2);
    printf("=======================================\n");
    // mat1 = [1,3;7,9];
    transpose(mat1, mat2);
    __show(2, mat2);
    rotate90(mat1, mat3);
    __show(3, mat3);
    printf("minimal of mat3 = %f\n", minOfMatrix(mat3));
    printf("maximal of mat3 = %f\n", maxOfMatrix(mat3));
    return 0;
}
