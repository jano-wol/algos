#include <gmock/gmock.h>

#include "./../../../applications/strings/count_substring_occurance/count_substring_occurance.h"

namespace
{
void testExpected(const std::string& str, const std::string& text, size_t expected)
{
  auto resultNaive = countSubstringOccuranceNaive(str, text);
  auto resultPrefixFunction = countSubstringOccurancePrefixFunction(str, text);
  auto resultZFunction = countSubstringOccuranceZFunction(str, text);
  auto resultHash = countSubstringOccuranceHash(str, text);
  auto resultAutomaton = countSubstringOccuranceAutomaton(str, text);
  EXPECT_EQ(resultNaive, expected);
  EXPECT_EQ(resultPrefixFunction, expected);
  EXPECT_EQ(resultZFunction, expected);
  EXPECT_EQ(resultHash, expected);
  EXPECT_EQ(resultAutomaton, expected);
}

void testAlignment(const std::string& str, const std::string& text)
{
  auto resultNaive = countSubstringOccuranceNaive(str, text);
  auto resultPrefixFunction = countSubstringOccurancePrefixFunction(str, text);
  auto resultZFunction = countSubstringOccuranceZFunction(str, text);
  auto resultHash = countSubstringOccuranceHash(str, text);
  auto resultAutomaton = countSubstringOccuranceAutomaton(str, text);
  EXPECT_EQ(resultNaive, resultPrefixFunction);
  EXPECT_EQ(resultNaive, resultZFunction);
  EXPECT_EQ(resultNaive, resultHash);
  EXPECT_EQ(resultNaive, resultAutomaton);
}
}  // namespace

TEST(CountSubstringOccurance, TestCountSubstringOccurance)
{
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
  testExpected("bbbaaabababbabbbaaaaabbbbbb", "bxb", 0);
  testExpected("bxb", "bbbaaabababbabbbaaaaabbbbbb", 0);
  testAlignment("bbbaaabababbabbbaaaaabbbbbb", "bbbaaabababbabbbaaaaabbbbbb");
  testAlignment("bbbaaabababbabbbaaaaabbbbbbaaa", "bbbaaabababbabbbaaaaabbbbbb");
  testAlignment("bb", "bbbaaabababbabbbaaaaabbbbbb");
  testAlignment("?#", "jGjjHG85_???##??###_843");
}