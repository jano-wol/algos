#include <gmock/gmock.h>

#include <cstring>

#include "./../../../algos/strings/prefix_function/prefix_function.h"
#include "./../../../algos/strings/prefix_function/prefix_function_naive.h"

TEST(PrefixFunction, TestPrefixFunction)
{
  std::string str = "aabaaab";
  auto pi = PrefixFunction::prefixFunction(str);
  auto piNaive = PrefixFunctionNaive::prefixFunction(str);
  std::vector<size_t> expected = {0, 1, 0, 1, 2, 2, 3};
  EXPECT_EQ(pi, expected);
  EXPECT_EQ(piNaive, expected);

  str = "";
  pi = PrefixFunction::prefixFunction(str);
  piNaive = PrefixFunctionNaive::prefixFunction(str);
  expected = {};
  EXPECT_EQ(pi, expected);
  EXPECT_EQ(piNaive, expected);

  str = "a";
  pi = PrefixFunction::prefixFunction(str);
  piNaive = PrefixFunctionNaive::prefixFunction(str);
  expected = {0};
  EXPECT_EQ(pi, expected);
  EXPECT_EQ(piNaive, expected);

  str = "aa";
  pi = PrefixFunction::prefixFunction(str);
  piNaive = PrefixFunctionNaive::prefixFunction(str);
  expected = {0, 1};
  EXPECT_EQ(pi, expected);
  EXPECT_EQ(piNaive, expected);

  str = "ab";
  pi = PrefixFunction::prefixFunction(str);
  piNaive = PrefixFunctionNaive::prefixFunction(str);
  expected = {0, 0};
  EXPECT_EQ(pi, expected);
  EXPECT_EQ(piNaive, expected);

  str = "bbbaaabababbabbbaaaaabbbbbb";
  pi = PrefixFunction::prefixFunction(str);
  piNaive = PrefixFunctionNaive::prefixFunction(str);
  EXPECT_EQ(pi, piNaive);

  str = "jGjjHG85_???##??###_843";
  pi = PrefixFunction::prefixFunction(str);
  piNaive = PrefixFunctionNaive::prefixFunction(str);
  EXPECT_EQ(pi, piNaive);
}
