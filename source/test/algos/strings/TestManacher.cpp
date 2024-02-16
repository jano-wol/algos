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
  testExpected("abcbcba", {{1, 1, 2, 4, 2, 1, 1}, {0, 0, 0, 0, 0, 0, 0}});
  testExpected("", {{}, {}});
  testExpected("a", {{1}, {0}});
  testExpected("aa", {{1, 1}, {0, 1}});
  testExpected("ab", {{1, 1}, {0, 0}});
  testExpected("aaa", {{1, 2, 1}, {0, 1, 1}});
  testExpected("aba", {{1, 2, 1}, {0, 0, 0}});
  testExpected("abba", {{1, 1, 1, 1}, {0, 0, 2, 0}});
  testExpected("abbaaaba", {{1, 1, 1, 1, 3, 1, 2, 1}, {0, 0, 2, 0, 1, 1, 0, 0}});
  testAlignment("bbbaaabababbabbbaaaaabbbbbb");
  testAlignment("jGjjHG85_???##??###_843");
}
