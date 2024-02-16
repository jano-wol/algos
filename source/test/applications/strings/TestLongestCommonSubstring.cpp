#include <gmock/gmock.h>

#include "./../../../applications/strings/longest_common_substring/longest_common_substring.h"

namespace
{
void checkResult(const std::string& str1, const std::string& str2, std::pair<size_t, std::pair<size_t, size_t>> result)
{
  const auto& [length, p] = result;
  const auto& [idx1, idx2] = p;
  auto candidate1 = str1.substr(idx1, length);
  auto candidate2 = str2.substr(idx2, length);
  EXPECT_EQ(candidate1, candidate2);
}

void testExpected(const std::string& str1, const std::string& str2, size_t expected)
{
  auto resultNaive = longestCommonSubstringNaive(str1, str2);
  auto resultKasai = longestCommonSubstringKasai(str1, str2);
  EXPECT_EQ(resultNaive.first, expected);
  EXPECT_EQ(resultKasai.first, expected);
  checkResult(str1, str2, resultNaive);
  checkResult(str1, str2, resultKasai);
}
}  // namespace

TEST(LongestCommonSubstring, TestLongestCommonSubstring)
{
  testExpected("", "", 0);
  testExpected("a", "", 0);
  testExpected("", "a", 0);
  testExpected("a", "a", 1);
  testExpected("a", "b", 0);
  testExpected("banana", "aaaabananaaaaaa", 6);
  testExpected("banana", "banana", 6);
  testExpected("aaaabananaaaaaa", "banana", 6);
  testExpected("xxxxbabababyyyyyyyy", "zzzzbabababqqqqqq", 7);
  testExpected("babababyyyyyyyy", "zzzzbabababqqqqqq", 7);
  testExpected("xxxxbababab", "zzzzbabababqqqqqq", 7);
  testExpected("xxxxbabababyyyyyyyy", "babababqqqqqq", 7);
  testExpected("xxxxbabababyyyyyyyy", "zzzzbababab", 7);
  testExpected("aaa", "aaaaa", 3);
  testExpected("aaaaa", "aaa", 3);
  testExpected("bbbbb", "aaaaaaaa", 0);
  testExpected("xxxxbabababyyybabababayyyyy", "zzzzbabababqqqbabababaqqq", 8);
}