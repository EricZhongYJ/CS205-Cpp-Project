// This file is for test. It will use specific seed to testify.
// If you want to get a totally random matrix, please use function rand_matrix like line 29.
// Author: 12012613 Zhong Yuanji钟元吉
// Encode: UTF-8
// Version: gcc (Ubuntu 11.2.0-19ubuntu1) 11.2.0
// Version: gcc (x86_64-posix-sjlj-rev0, Built by MinGW-W64 project) 12.2.0
// Date: 2022/11/27

#include "./inc/MoreFunc.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define __TimeStart __TBeg = clock();
#define __TimeEnd(str) \
    printf("%s %f s.\n", (str), (clock() - __TBeg) / (float)CLOCKS_PER_SEC);

clock_t __TBeg;
int main(int argc, char const *argv[])
{
    Matrix *mats[20];
    for (int i = 0; i < 20; ++i)
        mats[i] = NULLMatrix;
    char *temp; // For output and freeing
    float diff; // For compare the correctness of two method
    int count;
    // WITH_SHOW:
    printf("========================show randomness========================\n");
    // rand_matrix(mats[0], 100.f, 16, 16);
    rand_matrix_seed(mats[0], 100.f, 16, 16, 1234);
    rand_matrix_seed(mats[1], 100.f, 16, 16, 5678);
    __show(0, mats[0]); // Check if the matrices are random
    __show(1, mats[1]);
    count = 0, diff = 0.f;
    for (int i = 0; i < 16 * 16; ++i)
        for (int j = 0; j < 16 * 16; ++j)
            if (mats[0]->data[i] == mats[1]->data[j])
                ++count;
    printf("The number of same value between two matrices is %d\n", count);
    for (int i = 0; i < 16 * 16; ++i)
        diff += mats[0]->data[i] / 16 / 16;
    printf("The mean of each element in the first matrix is %f\n", diff);
    printf("========================check for 16x16========================\n");
    __TimeStart;
    matmul_plain(mats[0], mats[1], mats[2]);
    __TimeEnd("matmul_plain    cost:");
    __TimeStart;
    matmul_improved(mats[0], mats[1], mats[3]);
    __TimeEnd("matmul_improved cost:");
    diff = 0.f;
    for (size_t i = 0; i < 16 * 16; ++i)
        diff += abs(mats[2]->data[i] - mats[3]->data[i]);
    printf("The average difference of answer by two methods is:%f\n", diff);
    for (int i = 0; i < 4; ++i)
        deleteMatrix(mats + i);
    // WITHOUT_SHOW:
    int NS[4] = {128, 1000, 2000, 4000};
    // int NS[4] = {128, 1000, 8000, 64000}; // Too large to alloc (nearly 15GB RAM)
    for (int k = 0; k < 4; ++k)
    {
        printf("========================check for %dx%d========================\n", NS[k], NS[k]);
        rand_matrix_seed(mats[4 * k + 4], 100.f, NS[k], NS[k], 4 * k + 4);
        rand_matrix_seed(mats[4 * k + 5], 100.f, NS[k], NS[k], 4 * k + 5);
        printf("Get random data from specific seed\n");
        __TimeStart;
        matmul_plain(mats[4 * k + 4], mats[4 * k + 5], mats[4 * k + 6]);
        __TimeEnd("matmul_plain    cost:");
        __TimeStart;
        matmul_improved(mats[4 * k + 4], mats[4 * k + 5], mats[4 * k + 7]);
        __TimeEnd("matmul_improved cost:");
        diff = 0.f;
        for (size_t i = 0; i < NS[k] * NS[k]; ++i)
            diff += abs(mats[4 * k + 6]->data[i] - mats[4 * k + 7]->data[i]) / NS[k] / NS[k];
        printf("The average difference of answer by two methods is:%f\n", diff);
        for (int i = 4 * k + 4; i < 4 * k + 8; ++i)
            deleteMatrix(mats + i);
    }
}
