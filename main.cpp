
#include "./sigma/sigmaUtils.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

// Instructions
#define _NOP 0
#define _EOF 1
#define _JMP 2
#define _MOV 3
#define _REG 4

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

void moveValue(long long &dest, long long &src) { dest = src; }

void moveValue(int &dest, int &src) { dest = src; }

void moveImmediate(long long &reg, int value) { reg = value; }

void moveImmediate(int &reg, int value) { reg = value; }

void execute(std::vector<int> &fileContent) {
  int instructionPointer = 0;

  // Registers (64-bit and 32-bit)
  long long a64 = 0, b64 = 0, c64 = 0, d64 = 0, e64 = 0, f64 = 0;
  int a32 = 0, b32 = 0, c32 = 0, d32 = 0, e32 = 0, f32 = 0;

  while (instructionPointer < fileContent.size()) {
    int currentOp = fileContent[instructionPointer];

    switch (currentOp) {
    case _NOP:
      instructionPointer++;
      break;

    case _EOF:
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

    default:
      std::cout << "Error: Unknown operation code at instruction "
                << instructionPointer << "\n";
      return;
    }

    // Output the register states for debugging
    std::cout << "a64: " << a64 << " b64: " << b64 << " c64: " << c64
              << " d64: " << d64 << " e64: " << e64 << " f64: " << f64 << "\n";
    std::cout << "a32: " << a32 << " b32: " << b32 << " c32: " << c32
              << " d32: " << d32 << " e32: " << e32 << " f32: " << f32 << "\n";
  }
}

int main(int argc, char *argv[]) {
  std::ifstream file(argv[1]);

  std::vector<int> fileContent;
  {
    std::string line;
    std::stringstream tempFileContent;

    while (std::getline(file, line)) {
      tempFileContent << line << std::endl;
    }

    fileContent =
        sigma::vectorOutOfStringBySeperator<int>(tempFileContent.str(), ", ");
  }

  execute(fileContent);

  return 0;
}
