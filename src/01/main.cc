#include <fstream>
#include <iostream>
#include <string>

int get_calibration_val(std::string &line) {
  const std::string spelled[9] =
      {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  const std::string digits = "0123456789";

  size_t first_digit = line.find_first_of(digits);
  size_t last_digit = line.find_last_of(digits);

  size_t first_substr = std::string::npos;
  int first_substr_val = -1;
  size_t last_substr = 0;
  int last_substr_val = -1;

#ifdef AOC_PART_2
  for (int i = 0; i < 9; ++i) {
    size_t curr = line.find(spelled[i]);
    if (curr != std::string::npos && curr < first_substr) {
      first_substr = curr;
      first_substr_val = i + 1;
    }

    curr = line.rfind(spelled[i]);
    if (curr != std::string::npos && curr > last_substr) {
      last_substr = curr;
      last_substr_val = i + 1;
    }
  }
#endif

  int left_digit = 0;
  if (first_digit != std::string::npos && first_digit <= first_substr)
    left_digit = line.at(first_digit) - '0';
  else if (first_substr != std::string::npos)
    left_digit = first_substr_val;

  int right_digit = last_substr_val;
  if (last_digit != std::string::npos && last_digit >= last_substr)
    right_digit = line.at(last_digit) - '0';

//  std::cout << left_digit * 10 + right_digit << std::endl;
  return left_digit * 10 + right_digit;
}

int get_calibration_sum(std::ifstream &file) {

  int sum = 0;
  std::string line;
  while (getline(file, line))
    sum += get_calibration_val(line);
  return sum;
}

int main() {
  std::ifstream input_file(AOC_INPUT_FILE);
  if (input_file.is_open()) {
    std::cout << get_calibration_sum(input_file);
  } else {
    std::cerr << "Couldn't open file" << std::endl;
  }
  input_file.close();
  return 0;
}