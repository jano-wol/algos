#include <gmock/gmock.h>

#include <optional>

#include "./../../../applications/strings/calc_different_substrings/calc_different_substrings.h"

namespace
{
void testExpected(const std::string& str, size_t expected)
{
  auto resultNaive = calcDifferentSubstringsNaive(str);
  auto resultKasai = calcDifferentSubstringsKasai(str);
  auto resultSubstringsAutomaton1 = calcDifferentSubstringsAutomaton1(str);
  auto resultSubstringsAutomaton2 = calcDifferentSubstringsAutomaton2(str);
  EXPECT_EQ(resultNaive, expected);
  EXPECT_EQ(resultKasai, expected);
  EXPECT_EQ(resultSubstringsAutomaton1, expected);
  EXPECT_EQ(resultSubstringsAutomaton2, expected);
}

void testAlignment(const std::string& str)
{
  auto resultNaive = calcDifferentSubstringsNaive(str);
  auto resultKasai = calcDifferentSubstringsKasai(str);
  auto resultSubstringsAutomaton1 = calcDifferentSubstringsAutomaton1(str);
  auto resultSubstringsAutomaton2 = calcDifferentSubstringsAutomaton2(str);
  EXPECT_EQ(resultNaive, resultKasai);
  EXPECT_EQ(resultNaive, resultSubstringsAutomaton1);
  EXPECT_EQ(resultNaive, resultSubstringsAutomaton2);
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
