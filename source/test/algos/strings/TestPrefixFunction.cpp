#include <gmock/gmock.h>

#include <cstring>

#include "./../../../algos/strings/prefix_function/prefix_function.h"
#include "./../../../algos/strings/prefix_function/prefix_function_naive.h"

TEST(PrefixFunction, TestPrefixFunction)
{
  std::string str = "aabaaab";
  auto pi = PrefixFunction::prefixFunction(str);
  auto piNaive = PrefixFunctionNaive::prefixFunction(str);

  for (auto a : piNaive) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  for (auto a : pi) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}
