#include <gmock/gmock.h>

#include "./../../../applications/data_structures/sliding_minimum/sliding_minimum.h"

namespace
{
template <typename T>
void testExpected(const std::vector<T>& v, size_t w, const std::vector<T>& expected)
{
  auto resultNaive = slidingMinimumNaive(v, w);
  EXPECT_EQ(resultNaive, expected);
}
}  // namespace

TEST(SlidingMinimum, TestSlidingMinimum)
{
  testExpected(std::vector<int>{}, 0, std::vector<int>{});
  testExpected(std::vector<int>{1}, 0, std::vector<int>{});
  testExpected(std::vector<int>{}, 1, std::vector<int>{});
  testExpected(std::vector<int>{1, 2, 5, 6}, 5, std::vector<int>{});
  testExpected(std::vector<int>{1}, 1, std::vector<int>{1});
  testExpected(std::vector<int>{2, 1}, 2, std::vector<int>{1});
  testExpected(std::vector<int>{1, 2}, 2, std::vector<int>{1});
  testExpected(std::vector<int>{9, 2, 7}, 3, std::vector<int>{2});
  testExpected(std::vector<int>{9, 2, 7, 8, 8, 3, 6}, 3, std::vector<int>{2, 2, 7, 3, 3});
  testExpected(std::vector<int>{9, 2, 7, 8, 8, 3, 6}, 1, std::vector<int>{9, 2, 7, 8, 8, 3, 6});
  testExpected(std::vector<int>{9, 2, 7, 8, 8, 3, 8, 8, 5, 6, 6, 7, 4}, 6, std::vector<int>{2, 2, 3, 3, 3, 3, 5, 4});
  testExpected(std::vector<size_t>{9, 2, 7, 8, 8, 3, 6}, 2, std::vector<size_t>{2, 2, 7, 8, 3, 3});
}
