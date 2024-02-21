#include <gmock/gmock.h>

#include "./../../../applications/data_structures/range_minimum_query/range_minimum_query.h"

namespace
{
template <typename T>
void testExpected(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries,
                  const std::vector<T>& expected)
{
  auto resultNaive = rangeMinimumQueryNaive(a, queries);
  EXPECT_EQ(resultNaive, expected);
}
}  // namespace

TEST(RangeMinimumQuery, TestRangeMinimumQuery)
{
  testExpected(std::vector<int>{}, {}, {});
}
