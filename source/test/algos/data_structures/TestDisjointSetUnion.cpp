#include <gmock/gmock.h>

#include <vector>

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union.h"

namespace
{
void testSizes(size_t n, std::vector<std::pair<size_t, size_t>> connections, std::vector<size_t> expected)
{
  DisjointSetUnion d(n);
  for (const auto& [a, b] : connections) {
    d.unionSets(a, b);
  }
  auto size = d.getSize();
  std::vector<size_t> sizes;
  for (size_t i = 0; i < n; ++i) {
    sizes.push_back(size[d.findSet(i)]);
  }
  EXPECT_EQ(sizes, expected);
}
}  // namespace

TEST(DisjointSetUnion, TestDisjointSetUnion)
{
  testSizes(0, {}, {});
  testSizes(1, {}, {1});
  testSizes(1, {{0, 0}}, {1});
  testSizes(2, {{0, 0}, {1, 1}}, {1, 1});
  testSizes(2, {}, {1, 1});
  testSizes(2, {{0, 1}, {0, 1}}, {2, 2});
  testSizes(3, {}, {1, 1, 1});
  testSizes(3, {{0, 1}}, {2, 2, 1});
  testSizes(3, {{0, 1}, {0, 1}}, {2, 2, 1});
  testSizes(3, {{0, 1}, {0, 2}}, {3, 3, 3});
  testSizes(3, {{0, 1}, {0, 2}, {1, 2}}, {3, 3, 3});
  testSizes(4, {}, {1, 1, 1, 1});
  testSizes(4, {{1, 3}}, {1, 2, 1, 2});
  testSizes(4, {{0, 1}, {2, 3}}, {2, 2, 2, 2});
  testSizes(4, {{0, 3}, {2, 3}}, {3, 1, 3, 3});
  testSizes(4, {{0, 3}, {2, 3}, {0, 2}}, {3, 1, 3, 3});
  testSizes(4, {{0, 3}, {2, 3}, {1, 3}}, {4, 4, 4, 4});
}
