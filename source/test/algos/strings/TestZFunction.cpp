#include <gmock/gmock.h>

#include <cstring>

#include "./../../../algos/strings/z_function/z_function.h"
#include "./../../../algos/strings/z_function/z_function_naive.h"

TEST(ZFunction, TestZFunction)
{
  std::string str = "aabaaab";
  auto z = ZFunction::zFunction(str);
  auto zNaive = ZFunctionNaive::zFunction(str);

  for (auto a : z) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  for (auto a : zNaive) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}
