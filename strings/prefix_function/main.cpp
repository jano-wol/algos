#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "prefix_function.h"

std::vector<size_t> naive(const std::string& str)
{
  size_t n = str.size();
  std::vector<size_t> pi(n);
  for (size_t i = 0; i < n; i++)
    for (size_t k = 0; k <= i; k++)
      if (str.substr(0, k) == str.substr(i - k + 1, k))
        pi[i] = k;
  return pi;
}

int main()
{
  std::string str = "aabaaab";
  auto result = PrefixFunction::prefixFunction(str);
  auto resultNaive = naive(str);

  for (auto a : result) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  for (auto a : resultNaive) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}