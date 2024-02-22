#include <gmock/gmock.h>

#include "./../../../applications/data_structures/range_minimum_query/range_minimum_query.h"

namespace
{
template <typename T>
void testExpected(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries,
                  const std::vector<T>& expected)
{
  auto resultNaive = rangeMinimumQueryNaive(a, queries);
  auto resultDisjointSetUnion = rangeMinimumQueryDisjointSetUnion(a, queries);
  auto resultSparseTable = rangeMinimumQuerySparseTable(a, queries);
  EXPECT_EQ(resultNaive, expected);
  EXPECT_EQ(resultDisjointSetUnion, expected);
  EXPECT_EQ(resultSparseTable, expected);
}
}  // namespace

TEST(RangeMinimumQuery, TestRangeMinimumQuery)
{
  testExpected(std::vector<int>{}, {}, {});
  testExpected(std::vector<int>{0}, {}, {});
  testExpected(std::vector<int>{0}, {{0, 0}}, {0});
  testExpected(std::vector<int>{0}, {{0, 0}, {0, 0}}, {0, 0});
  testExpected(std::vector<int>{7, 6, 3, 2, 4, 5, -1, -4, 3, 6, 7}, {{5, 5}, {2, 8}, {4, 6}}, {5, -4, -1});
  testExpected(std::vector<int>{7, 6, 3, 2, 4, 5, -1, -4, 3, 6, 7}, {{3, 9}, {0, 0}, {8, 9}}, {-4, 7, 3});
  testExpected(std::vector<int>{7, 6, 3, 2, 4, 5, -1, -4, 3, 6, 7}, {{9, 10}, {2, 3}, {4, 6}}, {6, 2, -1});
  testExpected(std::vector<size_t>{5, 4, 3, 2, 5, 4, 3, 2}, {{0, 4}, {2, 3}, {4, 6}}, {2, 2, 3});
}
