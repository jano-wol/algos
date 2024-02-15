#include <gmock/gmock.h>

#include <cstring>

#include "./../../../applications/strings/calc_different_substrings/calc_different_substrings.h"

TEST(CalcDifferentSubstrings, TestCalcDifferentSubstrings)
{
  std::string str = "banana";
  std::cout << calcDifferentSubstringsNaive(str) << "\n";
  std::cout << calcDifferentSubstringsKasai(str) << "\n";
  std::cout << calcDifferentSubstringsAutomaton1(str) << "\n";
  std::cout << calcDifferentSubstringsAutomaton2(str) << "\n";
}