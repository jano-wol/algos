#include <gmock/gmock.h>

#include "./../../../../applications/graphs/bridges/bridges.h"

namespace
{
void testBridges(size_t n, const std::vector<std::pair<size_t, size_t>>& edges, std::vector<size_t> expected)
{
  auto resultNaive = bridgesNaive(n, edges);
  std::sort(expected.begin(), expected.end());
  std::sort(resultNaive.begin(), resultNaive.end());
  EXPECT_EQ(resultNaive, expected);
}
}  // namespace

TEST(Bridges, TestBridges) { testBridges(0, {}, {}); }
