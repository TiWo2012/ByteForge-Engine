#include "./sigma/sigmaUtils.hpp"
#include "src/assembler.hpp"
#include "src/runner.hpp"
#include "src/types.hpp"
#include <fstream>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

void prepareExecute(std::ifstream &file) {
  std::vector<int> fileContent;
  std::string line;
  std::stringstream tempFileContent;

  while (std::getline(file, line)) {
    tempFileContent << line << std::endl;
  }

  fileContent =
      sigma::vectorOutOfStringBySeperator<int>(tempFileContent.str(), ", ");
  execute(fileContent);
}

void prepareAssembler(std::ifstream &file) {
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

int main(int argc, char *argv[]) {
  if ((std::string)argv[1] == "-exec") {
    std::ifstream file(argv[2]);
    prepareExecute(file);
  } else if ((std::string)argv[1] == "-asm") {
    std::ifstream file(argv[2]);
    prepareAssembler(file);
  } else if ((std::string)argv[1] == "-v") {
    std::cout << "ByteForge Engine version: " << VERSION << std::endl;
  }

  return 0;
}
