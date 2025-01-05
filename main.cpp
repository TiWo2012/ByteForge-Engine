#include "./sigma/sigmaFiles.hpp"
#include "./sigma/sigmaUtils.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#define DEBUG 0

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

void pushVal(int val, std::ofstream &out) { out << val << ", "; }

void assemble(std::vector<std::string> fileContent) {
  std::ofstream out("a.byt");
  int instructionPointer = 0;

  while (instructionPointer < fileContent.size()) {
    std::string currOp = fileContent[instructionPointer];

    if (currOp == "nop") {
      pushVal(0, out);
      instructionPointer++;
    } else if (currOp == "EOF") {
      pushVal(1, out);
      instructionPointer++;
    } else if (currOp == "jmp") {
      pushVal(2, out);
      pushVal(std::stoi(fileContent[instructionPointer + 1]), out);
      instructionPointer += 2;
    } else if (currOp == "mov") {
      pushVal(3, out);
      if (sigma::grep(fileContent[instructionPointer + 1], "a64")) {
        pushVal(901, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "b64")) {
        pushVal(902, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "c64")) {
        pushVal(903, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "d64")) {
        pushVal(904, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "e64")) {
        pushVal(905, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "f64")) {
        pushVal(906, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "a32")) {
        pushVal(1001, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "b32")) {
        pushVal(1002, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "c32")) {
        pushVal(1003, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "d32")) {
        pushVal(1004, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "e32")) {
        pushVal(1005, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "f32")) {
        pushVal(1006, out);
      }

      if (sigma::grep(fileContent[instructionPointer + 2], "a64")) {
        pushVal(4, out);
        pushVal(901, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "b64")) {
        pushVal(4, out);
        pushVal(902, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "c64")) {
        pushVal(4, out);
        pushVal(903, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "d64")) {
        pushVal(4, out);
        pushVal(904, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "e64")) {
        pushVal(4, out);
        pushVal(905, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "f64")) {
        pushVal(4, out);
        pushVal(906, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "a32")) {
        pushVal(4, out);
        pushVal(1001, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "b32")) {
        pushVal(4, out);
        pushVal(1002, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "c32")) {
        pushVal(4, out);
        pushVal(1003, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "d32")) {
        pushVal(4, out);
        pushVal(1004, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "e32")) {
        pushVal(4, out);
        pushVal(1005, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "f32")) {
        pushVal(4, out);
        pushVal(1006, out);
        instructionPointer += 4;
      } else {
        pushVal(std::stoi(fileContent[instructionPointer + 2]), out);
        instructionPointer += 3;
      }

    } else if (currOp == "print") {
      pushVal(5, out);
      instructionPointer++;
    } else if (currOp == "pop") {
      pushVal(6, out);
      instructionPointer++;
    } else if (currOp == "push") {
      pushVal(7, out);
      instructionPointer++;
    } else if (currOp == "stack_Clear") {
      pushVal(8, out);
      instructionPointer++;
    } else if (currOp == "jiz") {
      pushVal(9, out);
      pushVal(std::stoi(fileContent[instructionPointer + 1]), out);
      instructionPointer += 2;
    } else if (currOp == "jnz") {
      pushVal(10, out);
      pushVal(std::stoi(fileContent[instructionPointer + 1]), out);
      instructionPointer += 2;
    } else if (currOp == "add") {
      pushVal(11, out);
      instructionPointer++;
    } else if (currOp == "sub") {
      pushVal(12, out);
      instructionPointer++;
    } else {
      std::cout << "Error: Unknown operation code at instruction "
                << instructionPointer << "\n";
      return;
    }
  }

  return;
}

int main(int argc, char *argv[]) {
  std::ifstream file(argv[2]);

  if ((std::string)argv[1] == "-exec") {
    std::vector<int> fileContent;
    std::string line;
    std::stringstream tempFileContent;

    while (std::getline(file, line)) {
      tempFileContent << line << std::endl;
    }

    fileContent =
        sigma::vectorOutOfStringBySeperator<int>(tempFileContent.str(), ", ");
    execute(fileContent);
  } else if ((std::string)argv[1] == "-asm") {
    std::vector<std::string> fileContent;
    std::string line;
    std::stringstream tempFileContent;

    while (std::getline(file, line)) {
      tempFileContent << line << std::endl;
    }

    fileContent = sigma::vectorOutOfStringBySeperator<std::string>(
        tempFileContent.str(), " ");
    assemble(fileContent);
  }

  return 0;
}
