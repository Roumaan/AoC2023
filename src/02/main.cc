#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::ifstream input_file("../../input/02/a.txt");
  if (input_file.is_open()) {

  } else {
    std::cerr << "Couldn't open file" << std::endl;
    input_file.close();
  }
  return 0;
}