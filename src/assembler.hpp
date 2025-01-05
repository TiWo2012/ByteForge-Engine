#pragma once

#include "../sigma/sigmaFiles.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

inline void pushVal(int val, std::ofstream &out) { out << val << ", "; }

inline void assemble(std::vector<std::string> fileContent) {
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
