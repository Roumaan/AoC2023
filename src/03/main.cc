#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <array>

int check_number(size_t nS, size_t nE, std::array<std::string, 3> lines) {
  std::istringstream iss(lines[1].substr(nS, nE - nS));
  int num_val;
  iss >> num_val;
  if ((nS > 0 && lines[1][nS - 1] != '.') ||
      (nE < lines[1].length() && lines[1][nE] != '.')) {
//    std::cout << lines[1][nS - 1] << ' ' << lines[1][nE] << std::endl;
    return num_val;
  }
  for (size_t i = (nS > 0 ? nS - 1 : 0); i <= nE; ++i) {
    if ((i < lines[0].length() && lines[0][i] != '.') ||
        (i < lines[2].length() && lines[2][i] != '.')) {
//      std::cout << ':' << lines[0][i] << ' ' << lines[2][i] << std::endl;
      return num_val;
    }
  }
  return 0;
}

int get_part_numbers_from_file(std::ifstream &file) {
  const std::string digits = "0123456789";

  int sum = 0;
  std::array<std::string, 3> lines = {"", "", ""};
  getline(file, lines[1]);
  while (!lines[1].empty()) {
    if (!getline(file, lines[2])) lines[2] = "";

    size_t nS = 0, nE = 0;
    while ((nS = lines[1].find_first_of(digits, nE)) < lines[1].length()) { ;
      nE = lines[1].find_first_not_of(digits, nS);
      if (nE == std::string::npos) nE = lines[1].length();

      int num = check_number(nS, nE, lines);
      sum += num;
//      std::cout << nS << ' ' << nE << std::endl;
//      std::cout << lines[0] << std::endl << lines[1] << std::endl << lines[2]
//                << std::endl << num << std::endl << std::endl;
    }

    lines[0] = lines[1];
    lines[1] = lines[2];
  }
  return sum;
}

int main() {
  std::ifstream input_file(AOC_INPUT_FILE);
  if (input_file.is_open()) {
#ifndef AOC_PART_2
    std::cout << get_part_numbers_from_file(input_file);
#else
    std::cout << get_minimum_sets(input_file);
#endif
  } else {
    std::cerr << "Couldn't open file" << std::endl;
    input_file.close();
  }
  return 0;
  return 0;
}