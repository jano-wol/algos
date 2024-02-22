#include <gmock/gmock.h>

#include <vector>

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union.h"
#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union_compress.h"
#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union_extra.h"

namespace
{
void testSizesDisjointSetUnion(size_t n, std::vector<std::pair<size_t, size_t>> connections,
                               std::vector<size_t> expected)
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

template <typename T>
void testSizesDisjointSetUnionExtra(size_t n, std::vector<std::pair<size_t, size_t>> connections,
                                    std::vector<size_t> expected)
{
  std::vector<T> s(n, 1);
  auto extraOp = [](size_t a, size_t b, std::vector<T>& extra) -> void { extra[a] += extra[b]; };
  DisjointSetUnionExtra<T> d(n, std::move(s), std::move(extraOp));
  for (const auto& [a, b] : connections) {
    d.unionSets(a, b);
  }
  auto size = d.getSize();
  std::vector<size_t> sizes1;
  for (size_t i = 0; i < n; ++i) {
    sizes1.push_back(size[d.findSet(i)]);
  }
  auto extra = d.getExtra();
  std::vector<size_t> sizes2;
  for (size_t i = 0; i < n; ++i) {
    sizes2.push_back(extra[d.findSet(i)]);
  }
  EXPECT_EQ(sizes1, expected);
  EXPECT_EQ(sizes2, expected);
}

void testSizesDisjointSetUnionCompress(size_t n, std::vector<std::pair<size_t, size_t>> connections, size_t source,
                                       size_t expected)
{
  DisjointSetUnionCompress d(n);
  for (const auto& [a, b] : connections) {
    d.connect(a, b);
  }
  EXPECT_EQ(d.findSet(source), expected);
}
}  // namespace

TEST(DisjointSetUnion, TestDisjointSetUnion)
{
  testSizesDisjointSetUnion(1, {{0, 0}}, {1});
  testSizesDisjointSetUnion(2, {{0, 0}, {1, 1}}, {1, 1});
  testSizesDisjointSetUnion(2, {}, {1, 1});
  testSizesDisjointSetUnion(2, {{0, 1}, {0, 1}}, {2, 2});
  testSizesDisjointSetUnion(3, {}, {1, 1, 1});
  testSizesDisjointSetUnion(3, {{0, 1}}, {2, 2, 1});
  testSizesDisjointSetUnion(3, {{0, 1}, {0, 1}}, {2, 2, 1});
  testSizesDisjointSetUnion(3, {{0, 1}, {0, 2}}, {3, 3, 3});
  testSizesDisjointSetUnion(3, {{0, 1}, {0, 2}, {1, 2}}, {3, 3, 3});
  testSizesDisjointSetUnion(4, {}, {1, 1, 1, 1});
  testSizesDisjointSetUnion(4, {{1, 3}}, {1, 2, 1, 2});
  testSizesDisjointSetUnion(4, {{0, 1}, {2, 3}}, {2, 2, 2, 2});
  testSizesDisjointSetUnion(4, {{0, 3}, {2, 3}}, {3, 1, 3, 3});
  testSizesDisjointSetUnion(4, {{0, 3}, {2, 3}, {0, 2}}, {3, 1, 3, 3});
  testSizesDisjointSetUnion(4, {{0, 3}, {2, 3}, {1, 3}}, {4, 4, 4, 4});
}

TEST(DisjointSetUnionExtra, TestDisjointSetUnionExtra)
{
  testSizesDisjointSetUnionExtra<int>(0, {}, {});
  testSizesDisjointSetUnionExtra<int>(1, {}, {1});
  testSizesDisjointSetUnionExtra<int>(1, {{0, 0}}, {1});
  testSizesDisjointSetUnionExtra<int>(2, {{0, 0}, {1, 1}}, {1, 1});
  testSizesDisjointSetUnionExtra<int>(2, {}, {1, 1});
  testSizesDisjointSetUnionExtra<int>(2, {{0, 1}, {0, 1}}, {2, 2});
  testSizesDisjointSetUnionExtra<int>(3, {}, {1, 1, 1});
  testSizesDisjointSetUnionExtra<int>(3, {{0, 1}}, {2, 2, 1});
  testSizesDisjointSetUnionExtra<int>(3, {{0, 1}, {0, 1}}, {2, 2, 1});
  testSizesDisjointSetUnionExtra<int>(3, {{0, 1}, {0, 2}}, {3, 3, 3});
  testSizesDisjointSetUnionExtra<int>(3, {{0, 1}, {0, 2}, {1, 2}}, {3, 3, 3});
  testSizesDisjointSetUnionExtra<int>(4, {}, {1, 1, 1, 1});
  testSizesDisjointSetUnionExtra<int>(4, {{1, 3}}, {1, 2, 1, 2});
  testSizesDisjointSetUnionExtra<int>(4, {{0, 1}, {2, 3}}, {2, 2, 2, 2});
  testSizesDisjointSetUnionExtra<int>(4, {{0, 3}, {2, 3}}, {3, 1, 3, 3});
  testSizesDisjointSetUnionExtra<int>(4, {{0, 3}, {2, 3}, {0, 2}}, {3, 1, 3, 3});
  testSizesDisjointSetUnionExtra<int>(4, {{0, 3}, {2, 3}, {1, 3}}, {4, 4, 4, 4});
}

TEST(DisjointSetUnionCompress, TestDisjointSetUnionCompress)
{
  DisjointSetUnionCompress d(0);
  testSizesDisjointSetUnionCompress(1, {}, 0, 0);
  testSizesDisjointSetUnionCompress(1, {{0, 0}}, 0, 0);
}