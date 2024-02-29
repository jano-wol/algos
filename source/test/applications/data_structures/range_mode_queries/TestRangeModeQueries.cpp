#include <gmock/gmock.h>

#include "./../../../../applications/data_structures/range_mode_query/range_mode_query.h"

namespace
{
template <typename T>
void testExpected(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries,
                  const std::vector<std::vector<T>>& expected)
{
  auto resultNaive = rangeModeQueryNaive(a, queries);
  // auto resultMo = rangeSumQueryMo(a, queries);
  EXPECT_EQ(resultNaive, expected);
  // EXPECT_EQ(resultMo, expected);
}
}  // namespace

TEST(RangeModeQuery, TestRangeModeQuery)
{
  testExpected(std::vector<int>{}, {}, {});
  testExpected(std::vector<int>{0}, {}, {});
  testExpected(std::vector<int>{0}, {{0, 0}}, {{0}});
  testExpected(std::vector<int>{0}, {{0, 0}, {0, 0}}, {{0}, {0}});
  testExpected(std::vector<int>{7, 6, 7, 6, 7, 6, 7}, {{0, 2}, {1, 3}, {2, 4}, {3, 5}, {4, 6}},
               {{7}, {6}, {7}, {6}, {7}});
  testExpected(std::vector<int>{7, 6, 7, 6, 7, 6, 7}, {{0, 3}, {1, 4}, {2, 5}, {3, 6}},
               {{6, 7}, {6, 7}, {6, 7}, {6, 7}});
  testExpected(std::vector<int>{7, 6, 7, 6, 7, 6, 7}, {{0, 6}, {1, 6}, {0, 5}, {1, 5}}, {{7}, {6, 7}, {6, 7}, {6}});
  testExpected(std::vector<int>{7, 6, 7, 6, 7, 6, 7}, {{0, 0}, {1, 1}, {2, 2}, {3, 3}, {1, 5}},
               {{7}, {6}, {7}, {6}, {6}});
  testExpected(std::vector<size_t>{7, 6, 7, 6, 7, 6, 7}, {{0, 6}}, {{7}});
  testExpected(std::vector<size_t>{7, 6, 7, 6, 7, 6, 7, 8, 8, 8, 8, 8},
               {{0, 6}, {0, 7}, {0, 8}, {0, 9}, {0, 10}, {0, 11}}, {{7}, {7}, {7}, {7}, {7, 8}, {8}});
  testExpected(std::vector<size_t>{8, 8, 8, 8, 8, 7, 6, 7, 6, 7, 6, 7},
               {{0, 11}, {1, 11}, {2, 11}, {3, 11}, {4, 11}, {5, 11}}, {{8}, {7, 8}, {7}, {7}, {7}, {7}});
}
