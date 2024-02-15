#include <gmock/gmock.h>

#include <cstring>
#include <optional>

#include "./../../../applications/strings/calc_different_substrings/calc_different_substrings.h"

namespace
{
void performTest(const std::string& str, std::optional<size_t> expected = std::nullopt)
{
  auto resultNaive = calcDifferentSubstringsNaive(str);
  auto resultKasai = calcDifferentSubstringsKasai(str);
  // auto resultSubstringsAutomaton1 = calcDifferentSubstringsAutomaton1(str);
  auto resultSubstringsAutomaton2 = calcDifferentSubstringsAutomaton2(str);
  if (!expected) {
    expected = resultNaive;
  }
  EXPECT_EQ(resultNaive, *expected);
  EXPECT_EQ(resultKasai, *expected);
  // EXPECT_EQ(resultSubstringsAutomaton1, *expected);
  EXPECT_EQ(resultSubstringsAutomaton2, *expected);
}
}  // namespace

TEST(CalcDifferentSubstrings, TestCalcDifferentSubstrings)
{
  performTest("banana", 15);
  performTest("", 0);
  performTest("a", 1);
  performTest("aa", 2);
  performTest("ab", 3);
  performTest("bbbaaabababbabbbaaaaabbbbbb");
  performTest("jGjjHG85_???##??###_843");
}
