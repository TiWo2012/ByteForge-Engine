#pragma once

#include <fstream>
#include <sstream>
#include <string>

namespace sigma {

// functionn to read from a file
inline void readFile(const std::string &filename, std::stringstream &content) {
  std::ifstream file(filename);
  if (file.is_open()) {
    content << file.rdbuf();
    file.close();
  }

  std::string Line;
  while (std::getline(file, Line)) {
    content << Line << std::endl;
  }
}

// function to write to a file
inline std::ofstream writeFile(const std::string &filename,
                               const std::string &content) {
  std::ofstream file(filename);
  if (file.is_open()) {
    file << content;
    file.close();
  }
  return file;
}

// function to find something in a stringstream and replace it with sommething
// else
inline std::string findAndReplace(const std::string &input,
                                  const std::string &find,
                                  const std::string &replace) {
  std::string output = input;
  std::size_t pos = 0;
  while ((pos = output.find(find, pos)) != std::string::npos) {
    output.replace(pos, find.length(), replace);
    pos += replace.length();
  }
  return output;
}

// function to grep thru a string and return true or false if found/not found
inline bool grep(const std::string &input, const std::string &find) {
  return input.find(find) != std::string::npos;
}

// function to return the length and size(using bytes, kilobytes, and so on) of
// a file.
inline std::string getFileSize(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  std::streamsize size = file.tellg();
  file.close();
  return std::to_string(size);
}

} // namespace sigma
