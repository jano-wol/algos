#include <gmock/gmock.h>

#include <optional>

#include "./../../../applications/strings/calc_different_substrings/calc_different_substrings.h"

namespace
{
void testExpected(const std::string& str, size_t expected)
{
  auto resultNaive = calcDifferentSubstringsNaive(str);
  auto resultKasai = calcDifferentSubstringsKasai(str);
  auto resultAutomaton1 = calcDifferentSubstringsAutomaton(str);
  auto resultHash = calcDifferentSubstringsHash(str);
  EXPECT_EQ(resultNaive, expected);
  EXPECT_EQ(resultKasai, expected);
  EXPECT_EQ(resultAutomaton1, expected);
  EXPECT_EQ(resultHash, expected);
}

void testAlignment(const std::string& str)
{
  auto resultNaive = calcDifferentSubstringsNaive(str);
  auto resultKasai = calcDifferentSubstringsKasai(str);
  auto resultAutomaton1 = calcDifferentSubstringsAutomaton(str);
  auto resultHash = calcDifferentSubstringsHash(str);
  EXPECT_EQ(resultNaive, resultKasai);
  EXPECT_EQ(resultNaive, resultAutomaton1);
  EXPECT_EQ(resultNaive, resultHash);
}
}  // namespace

TEST(CalcDifferentSubstrings, TestCalcDifferentSubstrings)
{
  testExpected("banana", 15);
  testExpected("", 0);
  testExpected("a", 1);
  testExpected("aa", 2);
  testExpected("ab", 3);
  testAlignment("bbbaaabababbabbbaaaaabbbbbb");
  testAlignment("jGjjHG85_???##??###_843");
}
