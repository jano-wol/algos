#include <gmock/gmock.h>

#include "./../../../applications/strings/prefix_freq/prefix_freq.h"

namespace
{
void testExpected(const std::string& str, const std::vector<size_t>& expected)
{
  auto result = prefixFreq(str);
  auto resultNaive = prefixFreqNaive(str);
  EXPECT_EQ(result, expected);
  EXPECT_EQ(resultNaive, expected);
}

void testAlignment(const std::string& str)
{
  auto result = prefixFreq(str);
  auto resultNaive = prefixFreqNaive(str);
  EXPECT_EQ(result, resultNaive);
}
}  // namespace

TEST(PrefixFreq, TestPrefixFreq)
{
  testExpected("aabaaabaaaba", {9, 5, 3, 3, 2, 2, 2, 2, 1, 1, 1, 1});
  testExpected("banana", {1, 1, 1, 1, 1, 1});
  testExpected("aaaa", {4, 3, 2, 1});
  testExpected("aa", {2, 1});
  testExpected("ab", {1, 1});
  testExpected("a", {1});
  testExpected("", {});
  testAlignment(std::string("bbbaaabababbabbbaaaaabbbbbb"));
  testAlignment(std::string("jGjjHG85_???##??###_843"));
}