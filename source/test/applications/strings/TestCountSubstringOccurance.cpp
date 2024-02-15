#include <gmock/gmock.h>

#include "./../../../applications/strings/count_substring_occurance/count_substring_occurance.h"

namespace
{
void testExpected(const std::string& str, const std::string& text, size_t expected)
{
  auto result = countSubstringOccurance(str, text);
  auto resultNaive = countSubstringOccuranceNaive(str, text);
  EXPECT_EQ(result, expected);
  EXPECT_EQ(resultNaive, expected);
}

void testAlignment(const std::string& str, const std::string& text)
{
  auto result = countSubstringOccurance(str, text);
  auto resultNaive = countSubstringOccuranceNaive(str, text);
  EXPECT_EQ(result, resultNaive);
}
}  // namespace

TEST(CountSubstringOccurance, TestCountSubstringOccurance)
{
  std::string str = "ab";
  std::string text = "aaaabababababababbbbbabbbb";
  testExpected("ab", "aaaabababababababbbbbabbbb", 8);
  testExpected("aab", "aaaabababababababbbbbabbbb", 1);
  testExpected("bab", "aaaabababababababbbbbabbbb", 7);
  testExpected("aaaa", "aaaaaaaa", 5);
  testExpected("b", "aaaaaaaa", 0);
  testExpected("", "", 0);
  testExpected("a", "", 0);
  testExpected("", "a", 0);
  testExpected("a", "a", 1);
  testExpected("a", "b", 0);
  testAlignment("bbbaaabababbabbbaaaaabbbbbb", "bbbaaabababbabbbaaaaabbbbbb");
  testAlignment("bb", "bbbaaabababbabbbaaaaabbbbbb");
  testAlignment("?#", "jGjjHG85_???##??###_843");
}