#include <gmock/gmock.h>

#include "./../../../applications/data_structures/interval_paint/interval_paint.h"

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
  testExpected(1, {{{0, 0}, 1}}, {1});
  testExpected(1, {{{0, 0}, 2}}, {2});
  testExpected(1, {{{0, 0}, 2}, {{0, 0}, 1}}, {1});
  testExpected(5, {{{1, 3}, 2}, {{2, 3}, 2}, {{2, 4}, 1}, {{0, 2}, 3}, {{0, 0}, 1}, {{2, 2}, 2}}, {1, 3, 2, 1, 1});
}
