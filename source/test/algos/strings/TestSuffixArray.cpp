#include <gmock/gmock.h>

#include <cstring>

#include "./../../../algos/strings/suffix_array/suffix_array.h"
#include "./../../../algos/strings/suffix_array/suffix_array_naive.h"

namespace
{
void testExpected(const std::string& str, const std::vector<size_t>& expected)
{
  auto result = SuffixArray::suffixArray(str);
  auto resultNaive = SuffixArrayNaive::suffixArray(str);
  EXPECT_EQ(result, expected);
  EXPECT_EQ(resultNaive, expected);
}

void testAlignment(const std::string& str)
{
  auto result = SuffixArray::suffixArray(str);
  auto resultNaive = SuffixArrayNaive::suffixArray(str);
  EXPECT_EQ(result, resultNaive);
}
}  // namespace

TEST(SuffixArray, TestSuffixArray)
{
  std::string str = "banana";
  testExpected("banana", {4, 3, 6, 2, 5, 1, 0});
  testExpected("", {0});
  testExpected("a", {1, 0});
  testExpected("aa", {2, 1, 0});
  testExpected("ab", {1, 2, 0});
  testAlignment("bbbaaabababbabbbaaaaabbbbbb");
  testAlignment("jGjjHG85_???##??###_843");
}
