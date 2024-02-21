#include <gmock/gmock.h>

#include "./../../../applications/data_structures/interval_paint/interval_paint.h"

namespace
{
void testExpected(size_t n, const std::vector<std::pair<std::pair<size_t, size_t>, size_t>>& queries,
                  const std::vector<size_t>& expected)
{
  auto resultNaive =  intervalPaintNaive(n, queries);
  EXPECT_EQ(resultNaive, expected);
}
}  // namespace

TEST(IntervalPaint, TestIntervalPaint)
{
  testExpected(0, {}, {});
}
