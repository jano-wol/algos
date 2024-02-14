#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "./../../../strings/prefix_function/prefix_function.h"

std::vector<size_t> prefixFunctionNaive(const std::string& str)
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
  auto piNaive = prefixFunctionNaive(str);
  auto pi = PrefixFunction::prefixFunction(str);

  for (auto a : piNaive) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  for (auto a : pi) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}
