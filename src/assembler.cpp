#include "assembler.hpp"
#include "types.hpp"

void pushVal(int val, std::ofstream &out) { out << val << ", "; }

void assemble(std::vector<std::string> fileContent) {
  std::ofstream out("a.byt");
  int instructionPointer = 0;

  while (instructionPointer < fileContent.size()) {
    std::string currOp = fileContent[instructionPointer];

    if (currOp == "nop") {
      pushVal(_NOP, out);
      instructionPointer++;
    } else if (currOp == "EOF") {
      pushVal(_EOF, out);
      instructionPointer++;
    } else if (currOp == "jmp") {
      pushVal(_JMP, out);
      pushVal(std::stoi(fileContent[instructionPointer + 1]), out);
      instructionPointer += 2;
    } else if (currOp == "mov") {
      pushVal(_MOV, out);
      if (sigma::grep(fileContent[instructionPointer + 1], "a64")) {
        pushVal(_64A, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "b64")) {
        pushVal(_64B, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "c64")) {
        pushVal(_64C, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "d64")) {
        pushVal(_64D, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "e64")) {
        pushVal(_64E, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "f64")) {
        pushVal(_64F, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "a32")) {
        pushVal(_32A, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "b32")) {
        pushVal(_32B, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "c32")) {
        pushVal(_32C, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "d32")) {
        pushVal(_32D, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "e32")) {
        pushVal(_32E, out);
      } else if (sigma::grep(fileContent[instructionPointer + 1], "f32")) {
        pushVal(_32F, out);
      }

      if (sigma::grep(fileContent[instructionPointer + 2], "a64")) {
        pushVal(_REG, out);
        pushVal(_64A, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "b64")) {
        pushVal(4, out);
        pushVal(_64B, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "c64")) {
        pushVal(4, out);
        pushVal(_64C, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "d64")) {
        pushVal(4, out);
        pushVal(_64D, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "e64")) {
        pushVal(4, out);
        pushVal(_64E, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "f64")) {
        pushVal(4, out);
        pushVal(_64F, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "a32")) {
        pushVal(4, out);
        pushVal(_32A, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "b32")) {
        pushVal(4, out);
        pushVal(_32B, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "c32")) {
        pushVal(4, out);
        pushVal(_32C, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "d32")) {
        pushVal(4, out);
        pushVal(_32D, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "e32")) {
        pushVal(4, out);
        pushVal(_32E, out);
        instructionPointer += 4;
      } else if (sigma::grep(fileContent[instructionPointer + 2], "f32")) {
        pushVal(4, out);
        pushVal(_32F, out);
        instructionPointer += 4;
      } else {
        pushVal(std::stoi(fileContent[instructionPointer + 2]), out);
        instructionPointer += 3;
      }

    } else if (currOp == "print") {
      pushVal(_PRINT, out);
      instructionPointer++;
    } else if (currOp == "pop") {
      pushVal(_POP, out);
      instructionPointer++;
    } else if (currOp == "push") {
      pushVal(_PUSH, out);
      instructionPointer++;
    } else if (currOp == "stack_Clear") {
      pushVal(_STACK_Clear, out);
      instructionPointer++;
    } else if (currOp == "jiz") {
      pushVal(_JIZ, out);
      pushVal(std::stoi(fileContent[instructionPointer + 1]), out);
      instructionPointer += 2;
    } else if (currOp == "jnz") {
      pushVal(_JNZ, out);
      pushVal(std::stoi(fileContent[instructionPointer + 1]), out);
      instructionPointer += 2;
    } else if (currOp == "add") {
      pushVal(_ADD, out);
      instructionPointer++;
    } else if (currOp == "sub") {
      pushVal(_SUB, out);
      instructionPointer++;
    } else if (currOp == "mul") {
      pushVal(_MUL, out);
    } else if (currOp == "div") {
      pushVal(_DIV, out);
    } else {
      std::cout << "Error: Unknown operation code at instruction "
                << instructionPointer << "\n";
      return;
    }
  }

  return;
}
