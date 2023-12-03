#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <array>

int check_part_number(size_t nS, size_t nE, std::array<std::string, 3> lines) {
  std::istringstream iss(lines[1].substr(nS, nE - nS));
  int num_val;
  iss >> num_val;
  if ((nS > 0 && lines[1][nS - 1] != '.') ||
      (nE < lines[1].length() && lines[1][nE] != '.'))
    return num_val;
  for (size_t i = (nS > 0 ? nS - 1 : 0); i <= nE; ++i)
    if ((i < lines[0].length() && lines[0][i] != '.') ||
        (i < lines[2].length() && lines[2][i] != '.'))
      return num_val;
  return 0;
}

int get_part_numbers_in_line(std::array<std::string, 3> lines) {
  const std::string digits = "0123456789";

  int sum = 0;
  size_t nS = 0, nE = 0;
  while ((nS = lines[1].find_first_of(digits, nE)) < lines[1].length()) { ;
    nE = lines[1].find_first_not_of(digits, nS);
    if (nE == std::string::npos) nE = lines[1].length();

    int num = check_part_number(nS, nE, lines);
    sum += num;
  }
  return sum;
}

int check_gear(size_t pos, std::array<std::string, 3> lines) {
  const std::string digits = "0123456789";

  size_t n1_x = 0, n1_y = 0, n2_x = 0, n2_y = 0;
  int n1_val = 0, n2_val = 0;
  for (size_t y = 0; y < 3; ++y)
    for (size_t x = pos - 1; x <= pos + 1 && x < lines[y].length(); ++x) {
      if (isdigit(lines[y][x])) {
        size_t n_s = lines[y].find_last_not_of(digits, x);
        n_s = (n_s != std::string::npos ? n_s + 1 : 0);
        size_t n_e = lines[y].find_first_not_of(digits, x);
        n_e = (n_e != std::string::npos ? n_e : lines[y].length());
        std::istringstream iss(lines[y].substr(n_s, n_e - n_s));
        if (n1_val == 0) {
          iss >> n1_val;
          n1_x = n_s;
          n1_y = y;
        } else if (n2_val == 0 && !(n_s == n1_x && y == n1_y)) {
          iss >> n2_val;
          n2_x = n_s;
          n2_y = y;
        } else if (!(n_s == n1_x && y == n1_y) && !(n_s == n2_x && y == n2_y)) {
          return 0;
        }
      }
    }
  return n1_val * n2_val;
}

int get_gears_in_line(std::array<std::string, 3> lines) {
  int sum = 0;

  size_t pos = 0;
  while ((pos = lines[1].find_first_of('*', pos + 1)) != std::string::npos) {
    sum += check_gear(pos, lines);
  }
  return sum;
}

int solve_file(std::ifstream &file) {

  int sum = 0;
  std::array<std::string, 3> lines = {"", "", ""};
  getline(file, lines[1]);
  while (!lines[1].empty()) {
    if (!getline(file, lines[2])) lines[2] = "";

#ifndef AOC_PART_2
    sum += get_part_numbers_in_line(lines);
#else
    sum += get_gears_in_line(lines);
#endif

    lines[0] = lines[1];
    lines[1] = lines[2];
  }
  return sum;
}

int main() {
  std::ifstream input_file(AOC_INPUT_FILE);
  if (input_file.is_open()) {
    std::cout << solve_file(input_file);
  } else {
    std::cerr << "Couldn't open file" << std::endl;
    input_file.close();
  }
  return 0;
}