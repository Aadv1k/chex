#include "../utils/utils.hpp"
#include "./board.hpp"
#include <iostream>

int main() {

  auto tokens = chex::splitString("foo,bar,baz", ',');
  std::cout << tokens[0] << std::endl;
  return 0;
}
