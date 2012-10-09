/**
 * NESToy emulator
 */
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

const int CARRY_FLAG = 0;
const int ZERO_FLAG = 1;
const int INTERRUPT_FLAG = 2;
const int DECIMAL_FLAG = 3;
const int BREAK_FLAG = 4;
const int DUMMY_FLAG = 5;
const int OVERFLOW_FLAG = 6;
const int SIGN_FLAG = 7;

#endif

#include <stdint.h>
typedef uint_least8_t uint8;
