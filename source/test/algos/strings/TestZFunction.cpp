#include <gmock/gmock.h>

#include "./../../../algos/strings/z_function/z_function.h"
#include "./../../../algos/strings/z_function/z_function_naive.h"

namespace
{
template <typename T>
void testExpected(const T& str, const std::vector<size_t>& expected)
{
  auto result = ZFunction::zFunction(str);
  auto resultNaive = ZFunctionNaive::zFunction(str);
  EXPECT_EQ(result, expected);
  EXPECT_EQ(resultNaive, expected);
}

template <typename T>
void testAlignment(const T& str)
{
  auto result = ZFunction::zFunction(str);
  auto resultNaive = ZFunctionNaive::zFunction(str);
  EXPECT_EQ(result, resultNaive);
}
}  // namespace

TEST(ZFunction, TestZFunction)
{
  testExpected(std::string("aabaaab"), {7, 1, 0, 2, 3, 1, 0});
  testExpected(std::vector<int>{0, 0, 1, 0, 0, 0, 1}, {7, 1, 0, 2, 3, 1, 0});
  testExpected(std::string(""), {});
  testExpected(std::vector<int>{}, {});
  testExpected(std::string("a"), {1});
  testExpected(std::string("aa"), {2, 1});
  testExpected(std::string("ab"), {2, 0});
  testAlignment(std::string("bbbaaabababbabbbaaaaabbbbbb"));
  testAlignment(std::string("jGjjHG85_???##??###_843"));
}
