#pragma once

// Store error type and position, type:
//  (format:) 1: invalid variable name     2: no input                    3: start with equal sign
//            4: invalid char              5: different number of ()      6: wrong number of nums or ops
//            7: number follow variable    8: operator follow operator / input start with operator
//  (number:) 9: more than one dots        10: float exponent             11: more than one 'e'
// (compute:) 12: divide by zero           13: include inf or nan         14: invalid operator
extern int error[]; // 2 part: type and position

// Construct object of constant
#define constPi Number((char *)"31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679\0", 1, -1)
#define constE Number((char *)"27182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274\0", 1, -1)
// Define the calculator precission of divide/powerI and clear0(total precission)
#define __PREC1 1500
// 2 * __PREC1 - 1
#define __PREC1N 2999
#define __PREC2 6000
// Solve the lond double problem in mingw in Windows
#if defined(__MINGW32_MINOR_VERSION) && __MINGW32_MINOR_VERSION < 10
typedef double ld; // in MinGW Low Version
#else
typedef long double ld; // in Linux
#endif

// Some function
#ifndef max
#define max(n1, n2) ((n1) > (n2) ? n1 : n2)
#endif