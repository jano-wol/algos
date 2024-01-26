#include <iostream>
#include <string>
#include <vector>

#include "suffix_array.h"

int main()
{
  std::string str = "banana";
  auto result = SuffixArray::suffixArray(str);

  for (auto a : result) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}