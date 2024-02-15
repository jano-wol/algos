#include <gmock/gmock.h>

#include <cstring>

#include "./../../../applications/strings/prefix_freq/prefix_freq.h"

TEST(PrefixFreq, TestPrefixFreq)
{
  std::string str = "aabaaabaaaba";

  auto resultNaive = prefixFreqNaive(str);
  auto result = prefixFreq(str);

  for (auto a : resultNaive) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  for (auto a : result) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}