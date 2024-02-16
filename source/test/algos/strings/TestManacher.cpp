#include <gmock/gmock.h>

#include "./../../../algos/strings/manacher/manacher.h"
#include "./../../../algos/strings/manacher/manacher_naive.h"

namespace
{
void testExpected(const std::string& str, const std::pair<std::vector<size_t>, std::vector<size_t>>& expected)
{
  auto result = Manacher::manacher(str);
  auto resultNaive = ManacherNaive::manacher(str);
  EXPECT_EQ(result, expected);
  EXPECT_EQ(resultNaive, expected);
}

void testAlignment(const std::string& str)
{
  auto result = Manacher::manacher(str);
  auto resultNaive = ManacherNaive::manacher(str);
  EXPECT_EQ(result, resultNaive);
}
}  // namespace

TEST(Manacher, TestManacher)
{
  testExpected("banana", {{1, 1, 2, 3, 2, 1}, {0, 0, 0, 0, 0, 0}});
/*   testExpected("abcbcba", {{6, 5, 3, 1, 0, 4, 2}, {0, 1, 3, 0, 0, 2}});
  testExpected("", {{0}, {}});
  testExpected("a", {{1, 0}, {0}});
  testExpected("aa", {{1, 0}, {0}});
  testExpected("ab", {{1, 0}, {0}});
  testAlignment("bbbaaabababbabbbaaaaabbbbbb");
  testAlignment("jGjjHG85_???##??###_843"); */
}
