#include <gmock/gmock.h>

#include <cstring>

#include "./../../../algos/strings/kasai/kasai.h"
#include "./../../../algos/strings/kasai/kasai_naive.h"

TEST(Kasai, TestKasai)
{
  std::string str = "banana";
  auto result = Kasai::kasai(str);
  auto resultNaive = KasaiNaive::kasai(str);
  std::pair<std::vector<size_t>, std::vector<size_t>> expected = {{6, 5, 3, 1, 0, 4, 2}, {0, 1, 3, 0, 0, 2}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(resultNaive, expected);

  str = "";
  result = Kasai::kasai(str);
  resultNaive = KasaiNaive::kasai(str);
  expected = {{0}, {}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(resultNaive, expected);

  str = "a";
  result = Kasai::kasai(str);
  resultNaive = KasaiNaive::kasai(str);
  expected = {{1, 0}, {0}};
  EXPECT_EQ(result, expected);
  EXPECT_EQ(resultNaive, expected);

  str = "bbbaaabababbabbbaaaaabbbbbb";
  result = Kasai::kasai(str);
  resultNaive = KasaiNaive::kasai(str);
  EXPECT_EQ(result, resultNaive);

  str = "jGjjHG85_???##??###_843";
  result = Kasai::kasai(str);
  resultNaive = KasaiNaive::kasai(str);
  EXPECT_EQ(result, resultNaive);
}
