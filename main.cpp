#include "./sigma/sigmaUtils.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

#define _NOP 0
#define _EOF 1

void execute(std::vector<int> &fileContent) {
  int i = 0;
  while (i < fileContent.size()) {
    if (fileContent[i] == _NOP) {
      i++;
    }

    if (fileContent[i] == _EOF) {
      std::cout << "EOF reached at operation " << i + 1 << "\n";
      return;
    }
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
