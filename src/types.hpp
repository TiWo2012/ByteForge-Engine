#pragma once

#define DEBUG 0
#define VERSION "0.1.1"
// Instructions
#define _NOP 0
#define _EOF 1
#define _JMP 2
#define _MOV 3
#define _REG 4
#define _PRINT 5
#define _POP 6
#define _PUSH 7
#define _STACK_Clear 8
#define _JIZ 9
#define _JNZ 10
#define _ADD 11
#define _SUB 12

// Registers (64 bit)
#define _64A 901
#define _64B 902
#define _64C 903
#define _64D 904
#define _64E 905
#define _64F 906

// Registers (32 bit)
#define _32A 1001
#define _32B 1002
#define _32C 1003
#define _32D 1004
#define _32E 1005
#define _32F 1006
