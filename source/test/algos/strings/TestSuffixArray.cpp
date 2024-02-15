#include <gmock/gmock.h>

#include <cstring>

#include "./../../../algos/strings/suffix_array/suffix_array.h"
#include "./../../../algos/strings/suffix_array/suffix_array_naive.h"

TEST(SuffixArray, TestSuffixArray)
{
  std::string str = "banana";
  auto result = SuffixArray::suffixArray(str);
  auto resultNaive = SuffixArray::suffixArray(str);

  for (auto a : resultNaive) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  for (auto a : result) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}
