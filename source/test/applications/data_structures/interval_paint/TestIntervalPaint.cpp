#include <gmock/gmock.h>

#include "./../../../../applications/data_structures/interval_paint/interval_paint.h"

namespace
{
void testExpected(size_t n, const std::vector<std::pair<std::pair<size_t, size_t>, size_t>>& queries,
                  const std::vector<size_t>& expected)
{
  auto resultNaive = intervalPaintNaive(n, queries);
  auto resultDisjointSetUnionExtra = intervalPaintDisjointSetUnionExtra(n, queries);
  EXPECT_EQ(resultNaive, expected);
  EXPECT_EQ(resultNaive, resultDisjointSetUnionExtra);
}
}  // namespace

TEST(IntervalPaint, TestIntervalPaint)
{
  testExpected(0, {}, {});
  testExpected(1, {}, {0});
  testExpected(1, {{{0, 0}, 0}}, {0});
  testExpected(1, {{{0, 0}, 1}}, {1});
  testExpected(1, {{{0, 0}, 2}}, {2});
  testExpected(1, {{{0, 0}, 2}, {{0, 0}, 1}}, {1});
  testExpected(5, {{{1, 3}, 2}, {{2, 3}, 2}, {{2, 4}, 1}, {{0, 2}, 3}, {{0, 0}, 1}, {{2, 2}, 2}}, {1, 3, 2, 1, 1});
  testExpected(15, {{{1, 7}, 2}, {{7, 10}, 2}, {{4, 11}, 5}, {{1, 2}, 6}, {{12, 14}, 1}, {{3, 9}, 3}, {{3, 5}, 2}},
               {0, 6, 6, 2, 2, 2, 3, 3, 3, 3, 5, 5, 1, 1, 1});
  testExpected(
      15, {{{1, 7}, 2}, {{7, 10}, 2}, {{4, 11}, 5}, {{1, 2}, 6}, {{12, 14}, 1}, {{3, 9}, 3}, {{3, 5}, 2}, {{9, 10}, 0}},
      {0, 6, 6, 2, 2, 2, 3, 3, 3, 0, 0, 5, 1, 1, 1});
  testExpected(15, {{{1, 1}, 2}, {{7, 7}, 2}, {{4, 4}, 5}, {{2, 2}, 6}, {{2, 2}, 3}, {{3, 3}, 3}, {{5, 5}, 2}},
               {0, 2, 3, 3, 5, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0});
  testExpected(6, {{{0, 1}, 1}, {{1, 2}, 2}, {{2, 3}, 3}, {{3, 4}, 4}, {{4, 5}, 5}}, {1, 2, 3, 4, 5, 5});
}
