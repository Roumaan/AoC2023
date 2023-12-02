#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int is_round_possible(std::string substring) {
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

int is_game_possible(std::string line) {
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

int main() {
  std::ifstream input_file(AOC_INPUT_FILE);
  if (input_file.is_open()) {
    std::cout << get_possible_games(input_file);
  } else {
    std::cerr << "Couldn't open file" << std::endl;
    input_file.close();
  }
  return 0;
}