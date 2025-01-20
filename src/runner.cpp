#include "runner.hpp"

#include "types.hpp"
#include <iostream>
#include <vector>

void moveValue(long long &dest, long long &src) { dest = src; }

void moveValue(int &dest, int &src) { dest = src; }

void moveImmediate(long long &reg, int value) { reg = value; }

void moveImmediate(int &reg, int value) { reg = value; }

void execute(std::vector<int> &fileContent) {
  int instructionPointer = 0;

  // Registers (64-bit and 32-bit)
  long long a64 = 0, b64 = 0, c64 = 0, d64 = 0, e64 = 0, f64 = 0;
  int a32 = 0, b32 = 0, c32 = 0, d32 = 0, e32 = 0, f32 = 0;

  // stack
  std::vector<char> stack;

  while (instructionPointer < fileContent.size()) {
    int currentOp = fileContent[instructionPointer];
    if (DEBUG)
      std::cout << "current instruction: " << currentOp << "\n";

    switch (currentOp) {
    case _NOP:
      instructionPointer++;
      break;

    case _EOF:
      if (DEBUG)
        std::cout << "EOF reached at operation " << instructionPointer + 1
                  << "\n";
      return;

    case _JMP:
      instructionPointer = fileContent[instructionPointer + 1];
      break;

    case _MOV: {
      int regType = fileContent[instructionPointer + 1];
      int operandType = fileContent[instructionPointer + 2];

      // 64-bit register move
      if (regType == _64A || regType == _64B || regType == _64C ||
          regType == _64D || regType == _64E || regType == _64F) {
        long long *targetReg = nullptr;
        long long *sourceReg = nullptr;
        int immediateValue = 0;

        if (operandType == _REG) {
          // Moving value between registers
          int srcReg = fileContent[instructionPointer + 3];
          targetReg = (regType == _64A)   ? &a64
                      : (regType == _64B) ? &b64
                      : (regType == _64C) ? &c64
                      : (regType == _64D) ? &d64
                      : (regType == _64E) ? &e64
                                          : &f64;

          sourceReg = (srcReg == _64A)   ? &a64
                      : (srcReg == _64B) ? &b64
                      : (srcReg == _64C) ? &c64
                      : (srcReg == _64D) ? &d64
                      : (srcReg == _64E) ? &e64
                                         : &f64;
          moveValue(*targetReg, *sourceReg);
          instructionPointer += 4;
        } else {
          // Immediate value move
          immediateValue = fileContent[instructionPointer + 2];
          targetReg = (regType == _64A)   ? &a64
                      : (regType == _64B) ? &b64
                      : (regType == _64C) ? &c64
                      : (regType == _64D) ? &d64
                      : (regType == _64E) ? &e64
                                          : &f64;
          moveImmediate(*targetReg, immediateValue);
          instructionPointer += 3;
        }
      }

      // 32-bit register move
      else if (regType == _32A || regType == _32B || regType == _32C ||
               regType == _32D || regType == _32E || regType == _32F) {
        int *targetReg = nullptr;
        int *sourceReg = nullptr;
        int immediateValue = 0;

        if (operandType == _REG) {
          // Moving value between registers
          int srcReg = fileContent[instructionPointer + 3];
          targetReg = (regType == _32A)   ? &a32
                      : (regType == _32B) ? &b32
                      : (regType == _32C) ? &c32
                      : (regType == _32D) ? &d32
                      : (regType == _32E) ? &e32
                                          : &f32;

          sourceReg = (srcReg == _32A)   ? &a32
                      : (srcReg == _32B) ? &b32
                      : (srcReg == _32C) ? &c32
                      : (srcReg == _32D) ? &d32
                      : (srcReg == _32E) ? &e32
                                         : &f32;
          moveValue(*targetReg, *sourceReg);
          instructionPointer += 4;
        } else {
          // Immediate value move
          immediateValue = fileContent[instructionPointer + 2];
          targetReg = (regType == _32A)   ? &a32
                      : (regType == _32B) ? &b32
                      : (regType == _32C) ? &c32
                      : (regType == _32D) ? &d32
                      : (regType == _32E) ? &e32
                                          : &f32;
          moveImmediate(*targetReg, immediateValue);
          instructionPointer += 3;
        }
      }

      break;
    }

    case _PRINT: {
      if (DEBUG)
        std::cout << "print statement reached\n";
      std::string stackStr = "";

      // Loop through the stack and append each value (converted to string) to
      // the stackStr
      for (size_t i = 0; i < stack.size(); i++) {
        stackStr += stack[i];
      }

      std::cout << stackStr << "\n";
      instructionPointer++;
      break;
    }

    case _POP:
      f32 = stack[stack.size() - 1];
      stack.pop_back();
      instructionPointer++;
      break;

    case _PUSH:
      stack.push_back((char)f32);
      instructionPointer++;
      break;

    case _STACK_Clear:
      stack.clear();
      instructionPointer++;
      break;

    case _JIZ:
      if (f64 == 0) {
        instructionPointer = fileContent[instructionPointer + 1];
      }
      instructionPointer += 2;
      break;

    case _JNZ:
      if (f64 != 0) {
        instructionPointer = fileContent[instructionPointer + 1];
      }
      instructionPointer += 2;
      break;

    case _ADD:
      a64 = a64 + b64;
      instructionPointer++;
      break;

    case _SUB:
      a64 = a64 - b64;
      instructionPointer++;
      break;

    case _MUL:
      a64 = a64 * b64;
      instructionPointer++;
      break;

    case _DIV:
      a64 = a64 / b64;
      instructionPointer++;
      break;

    default:
      std::cout << "Error: Unknown operation code at instruction "
                << instructionPointer << "\n";
      return;
    }

    if (DEBUG) {
      // Output the register states for debugging
      std::cout << "a64: " << a64 << " b64: " << b64 << " c64: " << c64
                << " d64: " << d64 << " e64: " << e64 << " f64: " << f64
                << "\n";
      std::cout << "a32: " << a32 << " b32: " << b32 << " c32: " << c32
                << " d32: " << d32 << " e32: " << e32 << " f32: " << f32
                << "\n";
    }
  }
}
