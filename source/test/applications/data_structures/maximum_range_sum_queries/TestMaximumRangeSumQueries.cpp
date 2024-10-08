#include <gmock/gmock.h>
#include <random>

#include "./../../../../applications/data_structures/maximum_range_sum_query/maximum_range_sum_query.h"

namespace
{
template <typename T>
void testExpected(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries,
                  const std::vector<T>& expected)
{
  auto resultNaive = maximumRangeSumQueryNaive(a, queries);
  auto resultDirect = maximumRangeSumQueryDirect(a, queries);
  auto resultSegmentTree = maximumRangeSumQuerySegmentTree(a, queries);
  EXPECT_EQ(resultNaive, expected);
  EXPECT_EQ(resultDirect, expected);
  EXPECT_EQ(resultSegmentTree, expected);
}

template <typename T>
void testRandom(size_t n)
{
  std::mt19937 e;
  std::vector<T> a(n);
  std::vector<std::pair<size_t, size_t>> queries;
  for (size_t idx = 0; idx < n; ++idx) {
    a[idx] = e() % 100 - 50;
  }
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i; j < n; ++j) {
      queries.push_back({i, j});
    }
  }
  auto resultNaive = maximumRangeSumQueryNaive(a, queries);
  auto resultDirect = maximumRangeSumQueryDirect(a, queries);
  auto resultSegmentTree = maximumRangeSumQuerySegmentTree(a, queries);
  EXPECT_EQ(resultNaive, resultDirect);
  EXPECT_EQ(resultNaive, resultSegmentTree);
}
}  // namespace

TEST(MaximumRangeSumQuery, TestMaximumRangeSumQuery)
{
  testExpected(std::vector<int>{}, {}, {});
  testExpected(std::vector<int>{0}, {}, {});
  testExpected(std::vector<int>{0}, {{0, 0}}, {0});
  testExpected(std::vector<int>{0}, {{0, 0}, {0, 0}}, {0, 0});
  testExpected(std::vector<int>{7, 6, 3, 2, 4, 5, -1, -4, 3, 6, 7}, {{5, 5}, {2, 8}, {4, 6}}, {5, 14, 9});
  testExpected(std::vector<int>{7, 6, 3, 2, 4, 5, -1, -4, 3, 6, 7}, {{3, 9}, {0, 0}, {8, 9}}, {15, 7, 9});
  testExpected(std::vector<int>{7, 6, 3, 2, 4, 5, -1, -4, 3, 6, 7}, {{9, 10}, {2, 3}, {4, 6}}, {13, 5, 9});
  testExpected(std::vector<size_t>{5, 4, 3, 2, 5, 4, 3, 2}, {{0, 4}, {2, 3}, {4, 6}}, {19, 5, 12});
  testExpected(std::vector<int>{5, -4, -3, -2, -5, 4, -3, 2}, {{0, 4}, {2, 3}, {4, 6}}, {5, 0, 4});
  testExpected(std::vector<int>{-5, -4, -3, -2, -5, -4, -3, -2},
               {{0, 4}, {2, 3}, {4, 6}, {0, 0}, {6, 6}, {7, 7}, {0, 7}}, {0, 0, 0, 0, 0, 0, 0});
  testExpected(std::vector<int>{-8, -4, 1, -2, 3, -2, 5, -5, 1, 3, -8, 1},
               {{0, 11}, {3, 11}, {4, 11}, {5, 11}, {7, 10}}, {6, 6, 6, 5, 4});
  for (size_t i = 0; i < 20; ++i) {
    testRandom<int>(i);
  }
}
