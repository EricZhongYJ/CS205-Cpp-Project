#pragma once

// Store error type and position, type:
//  (format:) 1: invalid variable name     2: no input                    3: start with equal sign
//            4: invalid char              5: different number of ()      6: wrong number of nums or ops
//            7: number follow variable    8: operator follow operator / input start with operator
//  (number:) 9: more than one dots        10: float exponent             11: more than one 'e'
// (compute:) 12: divide by zero           13: include inf or nan         14: invalid operator
extern int error[]; // 2 part: type and position

// Construct object of constant
#ifndef constPi
#define constPi Number((char *)"31415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679\0", 1, -1)
#endif
#ifndef constE
#define constE Number((char *)"27182818284590452353602874713526624977572470936999595749669676277240766303535475945713821785251664274\0", 1, -1)
#endif

// Some function
#ifndef max
#define max(n1, n2) ((n1) > (n2) ? n1 : n2)
#endif