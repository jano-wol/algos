#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "z_function.h"

std::vector<size_t> naive(const std::string& str)
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

size_t naiveCompress(const std::string& str)
{
  if (str.empty()) {
    return 0;
  }
  auto n = str.size();
  for (size_t i = 1; i <= n; ++i) {
    if (n % i != 0) {
      continue;
    }
    auto curr = str.substr(0, i);
    bool compressSuccess = true;
    for (size_t j = 0; j < n / i; ++j) {
      auto curr2 = str.substr(j * i, i);
      if (curr != curr2) {
        compressSuccess = false;
        break;
      }
    }
    if (compressSuccess) {
      return i;
    }
  }
  return 0;
}

// runtime = O(n), memory = O(n), where n = |str|.
size_t compress(const std::string& str)
{
  if (str.empty()) {
    return 0;
  }
  auto n = str.size();
  auto z = ZFunction::zFunction(str);
  for (size_t i = 1; i < n; ++i) {
    if (n % i != 0) {
      continue;
    }
    if (i + z[i] == n) {
      return i;
    }
  }
  return n;
}

int main()
{
  std::string str = "aabaaab";
  auto z = ZFunction::zFunction(str);
  auto zNaive = naive(str);

  for (auto a : z) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  for (auto a : zNaive) {
    std::cout << a << " ";
  }
  std::cout << "\n---------\n";

  str = "aabaaabaaaba";
  std::cout << naiveCompress(str) << "\n";
  std::cout << compress(str) << "\n---------\n";
}
