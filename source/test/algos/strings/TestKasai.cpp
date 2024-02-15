#include <gmock/gmock.h>

#include <cstring>

#include "./../../../algos/strings/kasai/kasai.h"
#include "./../../../algos/strings/kasai/kasai_naive.h"

TEST(Kasai, TestKasai)
{
  std::string str = "banana";
  auto result = Kasai::kasai(str);
  auto resultNaive = KasaiNaive::kasai(str);
  std::vector<size_t> expectedP = {6, 5, 3, 1, 0, 4, 2};
  std::vector<size_t> expectedLcp = {0, 1, 3, 0, 0, 2};
  EXPECT_EQ(result.first, expectedP);
  EXPECT_EQ(resultNaive.first, expectedP);
  EXPECT_EQ(result.second, expectedLcp);
  EXPECT_EQ(resultNaive.second, expectedLcp);

  str = "";
  result = Kasai::kasai(str);
  resultNaive = KasaiNaive::kasai(str);
  expectedP = {0};
  expectedLcp = {};
  EXPECT_EQ(result.first, expectedP);
  EXPECT_EQ(resultNaive.first, expectedP);
  EXPECT_EQ(result.second, expectedLcp);
  EXPECT_EQ(resultNaive.second, expectedLcp);

  str = "a";
  result = Kasai::kasai(str);
  resultNaive = KasaiNaive::kasai(str);
  expectedP = {1, 0};
  expectedLcp = {0};
  EXPECT_EQ(result.first, expectedP);
  EXPECT_EQ(resultNaive.first, expectedP);
  EXPECT_EQ(result.second, expectedLcp);
  EXPECT_EQ(resultNaive.second, expectedLcp);

  str = "bbbaaabababbabbbaaaaabbbbbb";
  result = Kasai::kasai(str);
  resultNaive = KasaiNaive::kasai(str);
  EXPECT_EQ(result, resultNaive);

  str = "jtoijGHZoignj584u359_dsjf???######____843";
  result = Kasai::kasai(str);
  resultNaive = KasaiNaive::kasai(str);
  EXPECT_EQ(result, resultNaive);
}
