#include <gmock/gmock.h>

#include "./../../../applications/strings/compress/compress.h"

namespace
{
void testExpected(const std::string& str, size_t expected)
{
  auto resultNaive = compressNaive(str);
  auto resultZFunction = compressZFunction(str);
  auto resultPrefixFunction = compressPrefixFunction(str);
  EXPECT_EQ(resultNaive, expected);
  EXPECT_EQ(resultZFunction, expected);
  EXPECT_EQ(resultPrefixFunction, expected);
}

void testAlignment(const std::string& str)
{
  auto resultNaive = compressNaive(str);
  auto resultZFunction = compressZFunction(str);
  auto resultPrefixFunction = compressPrefixFunction(str);
  EXPECT_EQ(resultNaive, resultZFunction);
  EXPECT_EQ(resultNaive, resultPrefixFunction);
}
}  // namespace

TEST(Compress, TestCompress)
{
  testExpected("aabaaabaaaba", 4);
  testExpected("aabaaabaaabaa", 13);
  testExpected("", 0);
  testExpected("a", 1);
  testExpected("aa", 1);
  testExpected("aaa", 1);
  testExpected("ab", 2);
  testExpected("abab", 2);
  testExpected("ababab", 2);
  testExpected("abababa", 7);
  testAlignment("bbbaaabababbabbbaaaaabbbbbb");
  testAlignment("jGjjHG85_???##??###_843");
}