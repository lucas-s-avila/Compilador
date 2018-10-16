#include <string>
#include <iostream>
#include <iterator>

int int main() {

  std::string entrada(std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>());

  return 0;
}
