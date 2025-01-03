#pragma once

#include "sigmaDefines.hpp"
#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <vector>

namespace sigma {

// functions for string manipulation

//  function to strip a defined string from a different string from left to
//  right
inline std::string stripLeft(const std::string &str,
                             const std::string &toStrip) {
  std::string result = str;
  std::size_t pos = result.find(toStrip);
  if (pos != std::string::npos) {
    result.erase(0, pos + toStrip.length());
  }
  return result;
}

inline std::string stripRight(const std::string &str,
                              const std::string &toStrip) {
  std::string result = str;
  std::size_t pos = result.find(toStrip);
  if (pos != std::string::npos) {
    result.erase(pos, toStrip.length());
  }
  return result;
}

inline std::string removeStringFromString(const std::string &str,
                                          const std::string &toRemove) {
  std::string result = str;
  std::size_t pos = result.find(toRemove);
  if (pos != std::string::npos) {
    result.erase(pos, toRemove.length());
  }
  return result;
}

inline std::string removeCharFromString(const std::string &str,
                                        const char toRemove) {
  std::string result = str;

  // Use erase-remove idiom to remove all occurrences of 'toRemove'
  result.erase(std::remove(result.begin(), result.end(), toRemove),
               result.end());

  return result;
}

inline std::string removeWhitespace(const std::string &str) {
  std::string result = str;
  result.erase(std::remove_if(result.begin(), result.end(),
                              [](unsigned char x) { return std::isspace(x); }),
               result.end());
  return result;
}

// debugfunctions
inline void Error(const std::string &msg) {
  std::cout << "ERROR: " << msg << "\n";
}

inline void Warning(const std::string &msg) {
  std::cout << "WARNING: " << msg << "\n";
}

inline void InfoString(const std::string &msg) {
  std::cout << "INFO: " << msg << "\n";
}

template <typename T> inline void InfoVal(const T &msg) {
  std::cout << "INFO: " << msg << "\n";
}

template <typename T> inline void Value(T value) { std::cout << value << "\n"; }

// functions involving arrays, sigma::cuboid and sigma::matrix
template <typename T, std::size_t N>
inline void printArray(const std::array<T, N> &arr) {
  for (std::size_t i = 0; i < arr.size(); i++) {
    std::cout << arr[i] << "\n";
  }
}

template <typename T> inline void printMatrix(const Matrix<T> &matrix) {
  for (std::size_t i = 0; i < matrix.size(); i++) {
    for (std::size_t j = 0; j < matrix[i].size(); j++) {
      std::cout << matrix[i][j] << " ";
    }
    std::cout << "\n";
  }
}

template <typename T> inline void printCuboid(const sigma::Cuboid<T> &cuboid) {
  for (std::size_t i = 0; i < cuboid.size(); i++) {
    for (std::size_t j = 0; j < cuboid[i].size(); j++) {
      for (std::size_t k = 0; k < cuboid[i][j].size(); k++) {
        std::cout << cuboid[i][j][k] << " ";
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }
}

template <typename T, std::size_t N>
inline std::array<T, N> arrayCopy(std::array<T, N> vec) {
  // allocate a temporary array
  std::array<T, N> temp;

  for (std::size_t i = 0; i < vec.size(); i++) {
    temp[i] = vec[i];
  }

  return temp;
}

template <typename T> inline std::vector<T> vectorCopy(std::vector<T> vec) {
  // allocate a temporary array
  std::vector<T> temp;

  for (std::size_t i = 0; i < vec.size(); i++) {
    temp.push_back(vec[i]);
  }

  return temp;
}

inline std::stringstream stringToStringstream(const std::string &str) {
  std::stringstream ss;
  ss << str;
  return ss;
}

inline std::string stringstreamToString(const std::stringstream &ss) {
  std::string str = ss.str();
  return str;
}

template <typename T>
inline std::vector<T>
vectorOutOfStringBySeperator(const std::string &str,
                             const std::string &seperator) {
  std::vector<T> result;
  std::stringstream ss(str);
  std::string token;
  while (std::getline(ss, token, seperator[0])) {
    std::istringstream iss(token);
    T temp;
    iss >> temp;
    result.push_back(temp);
  }
  return result;
}

} // namespace sigma
