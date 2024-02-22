#include <gmock/gmock.h>

#include <random>

#include "./../../../applications/graphs/least_common_ancestor/least_common_ancestor.h"

namespace
{
void testLeastCommonAncestor(size_t n, std::vector<std::pair<size_t, size_t>> edges,
                             std::vector<std::pair<size_t, size_t>> queries, std::vector<size_t> expected)
{
  auto resultNaive = leastCommonAncestorNaive(n, edges, queries);
  auto resultDisjointSetUnion = leastCommonAncestorDisjointSetUnion(n, edges, queries);
  EXPECT_EQ(resultNaive, expected);
  EXPECT_EQ(resultDisjointSetUnion, expected);
}
}  // namespace

TEST(LeastCommonAncestor, TestLeastCommonAncestor)
{
  testLeastCommonAncestor(0, {}, {}, {});
  testLeastCommonAncestor(1, {}, {}, {});
  testLeastCommonAncestor(1, {}, {{0, 0}}, {0});
  testLeastCommonAncestor(2, {{0, 1}}, {{0, 0}, {1, 0}, {1, 1}}, {0, 0, 1});
  testLeastCommonAncestor(2, {{0, 1}}, {{0, 0}, {0, 1}, {1, 1}}, {0, 0, 1});
  testLeastCommonAncestor(2, {{1, 0}}, {{0, 0}, {0, 1}, {1, 1}}, {0, 1, 1});
  testLeastCommonAncestor(7, {{2, 0}, {2, 1}, {3, 2}, {3, 4}, {4, 5}, {4, 6}},
                          {{0, 0}, {0, 1}, {0, 5}, {0, 6}, {1, 3}, {2, 4}, {6, 4}}, {0, 2, 3, 3, 3, 3, 4});
}
