#include <gmock/gmock.h>

#include <random>

#include "./../../../applications/graphs/least_common_ancestor/least_common_ancestor.h"

namespace
{
void testLeastCommonAncestor(size_t n, std::vector<std::pair<size_t, size_t>> edges,
                             std::vector<std::pair<size_t, size_t>> querys, std::vector<size_t> expected)
{
  auto resultNaive = leastCommonAncestorNaive(n, edges, querys);
  EXPECT_EQ(resultNaive, expected);
}
}  // namespace

TEST(LeastCommonAncestor, TestLeastCommonAncestor)
{
  testLeastCommonAncestor(0, {}, {}, {});
  testLeastCommonAncestor(1, {}, {}, {});
  testLeastCommonAncestor(1, {}, {{0, 0}}, {0});
  testLeastCommonAncestor(1, {{0, 0}}, {{0, 0}}, {0});
}
