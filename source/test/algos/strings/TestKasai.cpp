#include <gmock/gmock.h>

#include "./../../../algos/strings/kasai/kasai.h"
#include "./../../../algos/strings/kasai/kasai_naive.h"

namespace
{
void testExpected(const std::string& str, const std::pair<std::vector<size_t>, std::vector<size_t>>& expected)
{
  auto result = Kasai::kasai(str);
  auto resultNaive = KasaiNaive::kasai(str);
  EXPECT_EQ(result, expected);
  EXPECT_EQ(resultNaive, expected);
}

void testAlignment(const std::string& str)
{
  auto result = Kasai::kasai(str);
  auto resultNaive = KasaiNaive::kasai(str);
  EXPECT_EQ(result, resultNaive);
}
}  // namespace

TEST(Kasai, TestKasai)
{
  testExpected("banana", {{6, 5, 3, 1, 0, 4, 2}, {0, 1, 3, 0, 0, 2}});
  testExpected("", {{0}, {}});
  testExpected("a", {{1, 0}, {0}});
  testAlignment("bbbaaabababbabbbaaaaabbbbbb");
  testAlignment("jGjjHG85_???##??###_843");
}
