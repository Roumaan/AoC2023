#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int is_round_possible(const std::string &substring) {
  const int max[3] = {12, 13, 14};
  const std::string colors[3]{"red", "green", "blue"};

  int is_possible = 1;
  int num = 0;
  std::string color;
  std::istringstream iss(substring);
  while (iss >> num && getline(iss >> std::ws, color, ','))
    for (int i = 0; i < 3; ++i)
      if (colors[i] == color) {
        if (num > max[i])
          is_possible = 0;
        break;
      }
  return is_possible;
}

int is_game_possible(const std::string &line) {
  std::istringstream iss(line.substr(line.find_first_of(':') + 2));
  std::string substr;
  int is_possible = 1;
  while (getline(iss, substr, ';')) {
    if (!is_round_possible(substr))
      is_possible = 0;
  }
  return is_possible;
}

int get_possible_games(std::ifstream &file) {
  int sum = 0;
  std::string line;
  for (int i = 0; getline(file, line); ++i)
    if (is_game_possible(line))
      sum += i + 1;
  return sum;
}

void adjust_min_set_for_round(const std::string &substring, int min_set[3]) {
  const std::string colors[3]{"red", "green", "blue"};

  int num = 0;
  std::string color;
  std::istringstream iss(substring);
  while (iss >> num && getline(iss >> std::ws, color, ','))
    for (int i = 0; i < 3; ++i)
      if (colors[i] == color && num > min_set[i])
        min_set[i] = num;
}

int get_minimum_game_set(const std::string &line) {
  int min_set[3] = {0};
  std::istringstream iss(line.substr(line.find_first_of(':') + 2));
  std::string substr;
  while (getline(iss, substr, ';'))
    adjust_min_set_for_round(substr, min_set);
  return min_set[0] * min_set[1] * min_set[2];
}

int get_minimum_sets(std::ifstream &file) {
  int sum = 0;
  std::string line;
  for (int i = 0; getline(file, line); ++i)
    sum += get_minimum_game_set(line);
  return sum;
}

int main() {
  std::ifstream input_file(AOC_INPUT_FILE);
  if (input_file.is_open()) {
#ifndef AOC_PART_2
    std::cout << get_possible_games(input_file);
#else
    std::cout << get_minimum_sets(input_file);
#endif
  } else {
    std::cerr << "Couldn't open file" << std::endl;
  }
  input_file.close();
  return 0;
}