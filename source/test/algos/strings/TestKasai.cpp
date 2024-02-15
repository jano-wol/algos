#include <gmock/gmock.h>

#include <cstring>

#include "./../../../algos/strings/kasai/kasai.h"
#include "./../../../algos/strings/kasai/kasai_naive.h"

TEST(Kasai, TestKasai)
{
  std::string str = "banana";
  auto result = Kasai::kasai(str);
  auto resultNaive = KasaiNaive::kasai(str);

  for (auto a : resultNaive.second) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  for (auto a : result.second) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}
