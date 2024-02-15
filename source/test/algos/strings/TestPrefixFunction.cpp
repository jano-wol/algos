#include <gmock/gmock.h>

#include "./../../../algos/strings/prefix_function/prefix_function.h"
#include "./../../../algos/strings/prefix_function/prefix_function_naive.h"

namespace
{
template <typename T>
void testExpected(const T& str, const std::vector<size_t>& expected)
{
  auto pi = PrefixFunction::prefixFunction(str);
  auto piNaive = PrefixFunctionNaive::prefixFunction(str);
  EXPECT_EQ(pi, expected);
  EXPECT_EQ(piNaive, expected);
}

template <typename T>
void testAlignment(const T& str)
{
  auto pi = PrefixFunction::prefixFunction(str);
  auto piNaive = PrefixFunctionNaive::prefixFunction(str);
  EXPECT_EQ(pi, piNaive);
}
}  // namespace

void testAlignment() {}

TEST(PrefixFunction, TestPrefixFunction)
{
  testExpected(std::string("aabaaab"), {0, 1, 0, 1, 2, 2, 3});
  testExpected(std::vector<int>{0, 0, 1, 0, 0, 0, 1}, {0, 1, 0, 1, 2, 2, 3});
  testExpected(std::string(""), {});
  testExpected(std::vector<int>{}, {});
  testExpected(std::string("a"), {0});
  testExpected(std::string("aa"), {0, 1});
  testExpected(std::string("ab"), {0, 0});
  testAlignment(std::string("bbbaaabababbabbbaaaaabbbbbb"));
  testAlignment(std::string("jGjjHG85_???##??###_843"));
}
