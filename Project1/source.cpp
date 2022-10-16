// This file is to compute the product of two numbers from the command line arguments.
// Author: 12012613 Zhong Yuanji钟元吉
// Encode: UTF-8
// Version: g++ (Ubuntu 11.2.0-19ubuntu1) 11.2.0
// Date: 2022/9/25
#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

// The main function
int main(int argc, char const *argv[])
{
    // Check if the number of inputs is 2
    if (argc != 3)
    {
        cout << "Please check the number of inputs. It must be 2." << endl;
        return 0;
    }

    // Check if inputs include float number or not a number (or have more than 1 dot or incorrct minus signal or other char)
    string name[] = {"", "first", "second"};
    int num1len = strlen(argv[1]), num2len = strlen(argv[2]);
    bool haveFloat = false, haveDot, haveE;
    for (short k = 1; k < 3; ++k)
    {
        haveDot = false, haveE = false;
        for (int i = 0; i < (int)strlen(argv[k]); ++i)
        {
            // Check if inputs include float number
            if (!haveFloat && (argv[k][i] == '.' || argv[k][i] == 'e' || argv[k][i] == 'E'))
            {
                haveFloat = true;
            }
            // Check if inputs include invalid char
            if (('0' > argv[k][i] || argv[k][i] > '9') && argv[k][i] != '.' && argv[k][i] != 'e' && argv[k][i] != 'E' && argv[k][i] != '-')
            {
                cout << "The " << name[k] << " input cannot be interpret as numbers! (invalid char)" << endl;
                return 0;
            }
            // Check if have more than one dots
            else if (argv[k][i] == '.')
            {
                if (haveE)
                {
                    cout << "The exponent of the " << name[k] << " number cannot be a float number." << endl;
                    return 0;
                }
                else if (!haveDot)
                {
                    haveDot = true;
                }
                else
                {
                    cout << "There are more than one dots in the " << name[k] << " number." << endl;
                    return 0;
                }
            }
            else if (argv[k][i] == 'e' || argv[k][i] == 'E')
            {
                // Check if the first char is 'e' or 'E'
                if (i == 0)
                {
                    cout << "The first char in the " << name[k] << " number cannot be \'e\' or \'E\'." << endl;
                    return 0;
                }
                // Check if have more than one 'e' or 'E'
                else if (!haveE)
                {
                    haveE = true;
                }
                else
                {
                    cout << "There are more than one \'e\' or \'E\' in the " << name[k] << " number." << endl;
                    return 0;
                }
            }
            // Check if have an incorrect minus signal
            else if (argv[k][i] == '-')
            {
                if (i != 0 && argv[k][i - 1] != 'e' && argv[k][i - 1] != 'E')
                {
                    cout << "There is an incorrect minus signal in the " << name[k] << " number." << endl;
                    return 0;
                }
            }
        }
    }

    // Divide float and int, compute and output
    if (haveFloat)
    {
        // Read and compute
        // ATTENTION: If the inputs include correct float, but output is "The inputs float numbers are too big.", that is because
        //            the version of g++ is too low. Please change the "long double" in next line into "double" and run again.
        long double num1, num2;
        sscanf(argv[1], "%Lf", &num1);
        sscanf(argv[2], "%Lf", &num2);
        long double num3 = num1 * num2;

        // Check if the number is too big and show result
        if (isnan(num3) || isinf(num3))
        {
            cout << "The input float numbers are too big." << endl;
        }
        else
        {
            cout << argv[1] << " * " << argv[2] << " = " << num3 << endl;
        }
    }
    else // Inputs are integers
    {
        // Judge the symbol of product
        char symbol = (argv[1][0] == '-' ? 1 : 0) + (argv[2][0] == '-' ? 1 : 0) % 2;
        // Read num1
        char num1[num1len], num2[num2len];
        for (int i = num1len - 1; i >= 0; --i)
        {
            if (i == 0 && argv[1][0] == '-')
            {
                num1[num1len - 1] = 0;
                break;
            }
            num1[num1len - 1 - i] = argv[1][i] - '0';
        }
        // Read num2
        for (int i = num2len - 1; i >= 0; --i)
        {
            if (i == 0 && argv[2][0] == '-')
            {
                num2[num2len - 1] = 0;
                break;
            }
            num2[num2len - 1 - i] = argv[2][i] - '0';
        }
        // Initial num3 and compute the product
        unsigned short num3[num1len + num2len];
        for (int i = 0; i < num1len + num2len; i++)
            num3[i] = 0;
        for (int i = 0; i < num1len * num2len; i++)
        {
            int x = i % num1len, y = i / num1len;
            num3[x + y] += num1[x] * num2[y];
        }
        for (int i = 0; i < num1len + num2len - 1; i++)
        {
            num3[i + 1] += num3[i] / 10;
            num3[i] %= 10;
        }
        // Show result
        cout << argv[1] << " * " << argv[2] << " = " << (symbol == 1 ? "-" : "");
        char unzero = 0;
        for (int i = num1len + num2len - 1; i >= 0; --i)
        {
            if (unzero != 0)
            {
                cout << num3[i];
            }
            else if (num3[i] != 0)
            {
                cout << num3[i];
                unzero = 1;
            }
        }
        cout << endl;
    }
    return 0;
}
