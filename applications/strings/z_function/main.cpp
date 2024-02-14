#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "./../../../strings/z_function/z_function.h"

std::vector<size_t> naiveZFunction(const std::string& str)
{
  size_t n = str.size();
  std::vector<size_t> z(n, 0);
  for (size_t i = 0; i < n; i++) {
    size_t intersect = 0;
    while (i + intersect < n && str[i + intersect] == str[intersect]) {
      ++intersect;
    }
    z[i] = intersect;
  }
  return z;
}

int main()
{
  std::string str = "aabaaab";
  auto z = ZFunction::zFunction(str);
  auto zNaive = naiveZFunction(str);

  for (auto a : z) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  for (auto a : zNaive) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}

