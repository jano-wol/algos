#include <gmock/gmock.h>

#include "./../../../../applications/data_structures/range_sum_query/range_sum_query.h"

namespace
{
template <typename T>
void testExpected(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries,
                  const std::vector<T>& expected)
{
  auto resultNaive = rangeSumQueryNaive(a, queries);
  auto resultSparseTable = rangeSumQuerySparseTable(a, queries);
  auto resultSparseTableDisjointSum = rangeSumQuerySparseTableDisjointSum(a, queries);
  auto resultFenwick = rangeSumQueryFenwick(a, queries);
  auto resultSqrtDecomposition = rangeSumQuerySqrtDecomposition(a, queries);
  auto resultMo = rangeSumQueryMo(a, queries);
  auto resultSegmentTree = rangeSumQuerySegmentTree(a, queries);
  auto resultSqrtTree = rangeSumQuerySqrtTree(a, queries);
  EXPECT_EQ(resultNaive, expected);
  EXPECT_EQ(resultSparseTable, expected);
  EXPECT_EQ(resultSparseTableDisjointSum, expected);
  EXPECT_EQ(resultFenwick, expected);
  EXPECT_EQ(resultSqrtDecomposition, expected);
  EXPECT_EQ(resultMo, expected);
  EXPECT_EQ(resultSegmentTree, expected);
  EXPECT_EQ(resultSqrtTree, expected);
}
}  // namespace

TEST(RangeSumQuery, TestRangeSumQuery)
{
  testExpected(std::vector<int>{}, {}, {});
  testExpected(std::vector<int>{0}, {}, {});
  testExpected(std::vector<int>{0}, {{0, 0}}, {0});
  testExpected(std::vector<int>{0}, {{0, 0}, {0, 0}}, {0, 0});
  testExpected(std::vector<int>{7, 6, 3, 2, 4, 5, -1, -4, 3, 6, 7}, {{5, 5}, {2, 8}, {4, 6}}, {5, 12, 8});
  testExpected(std::vector<int>{7, 6, 3, 2, 4, 5, -1, -4, 3, 6, 7}, {{3, 9}, {0, 0}, {8, 9}}, {15, 7, 9});
  testExpected(std::vector<int>{7, 6, 3, 2, 4, 5, -1, -4, 3, 6, 7}, {{9, 10}, {2, 3}, {4, 6}}, {13, 5, 8});
  testExpected(std::vector<size_t>{5, 4, 3, 2, 5, 4, 3, 2}, {{0, 4}, {2, 3}, {4, 6}}, {19, 5, 12});
}
