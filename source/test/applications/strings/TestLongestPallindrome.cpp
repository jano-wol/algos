#include <gmock/gmock.h>

#include "./../../../applications/strings/longest_pallindrome/longest_pallindrome.h"

namespace
{
void testExpected(const std::string& str, const std::pair<size_t, size_t>& expected)
{
  auto resultNaive = longestPallindromeNaive(str);
  EXPECT_EQ(resultNaive, expected);
}
}  // namespace

TEST(LongestPallindrome, TestLongestPallindrome)
{
  testExpected("banana", {1, 6});
  testExpected("aabaaabaaaba", {1, 12});
  testExpected("abcdef", {0, 1});
  testExpected("abcddcef", {2, 6});
  testExpected("", {0, 0});
  testExpected("a", {0, 1});
  testExpected("aa", {0, 2});
  testExpected("aaa", {0, 3});
  testExpected("ab", {0, 1});
  testExpected("abab", {0, 3});
  testExpected("ababa", {0, 5});
  testExpected("bbbaaabababbabbbaaaaabbbbbb", {13, 24});
  testExpected("jGjjHG85_???##??###_843", {10, 16});
}