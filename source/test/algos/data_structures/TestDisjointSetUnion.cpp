#include <gmock/gmock.h>

#include <random>
#include <set>
#include <vector>

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union.h"
#include "./../../../applications/graphs/number_of_components/number_of_components.h"

namespace
{
void testNumberOfComponents(size_t n, std::vector<std::pair<size_t, size_t>> connections, size_t expected)
{
  DisjointSetUnion d(n);
  for (const auto& [a, b] : connections) {
    d.unionSets(a, b);
  }
  EXPECT_EQ(d.getNumberOfComponents(), expected);
}

void testRandomGraph(size_t n, double p)
{
  DisjointSetUnion d(n);
  std::vector<std::pair<size_t, size_t>> edges;
  std::mt19937 e;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (static_cast<double>(e() % 100) < p * 100.0) {
        d.unionSets(i, j);
        edges.push_back({i, j});
      }
    }
  }
  EXPECT_EQ(d.getNumberOfComponents(), numberOfComponentsNaive(n, edges));
}
}  // namespace

TEST(DisjointSetUnion, TestDisjointSetUnion)
{
  testNumberOfComponents(0, {}, 0);
  testNumberOfComponents(1, {}, 1);
  testNumberOfComponents(1, {{0, 0}}, 1);
  testNumberOfComponents(2, {{0, 0}, {1, 1}}, 2);
  testNumberOfComponents(2, {}, 2);
  testNumberOfComponents(2, {{0, 1}, {0, 1}}, 1);
  testNumberOfComponents(3, {}, 3);
  testNumberOfComponents(3, {{0, 1}}, 2);
  testNumberOfComponents(3, {{0, 1}, {0, 1}}, 2);
  testNumberOfComponents(3, {{0, 1}, {0, 2}}, 1);
  testNumberOfComponents(3, {{0, 1}, {0, 2}, {1, 2}}, 1);
  testNumberOfComponents(4, {}, 4);
  testNumberOfComponents(4, {{1, 3}}, 3);
  testNumberOfComponents(4, {{0, 1}, {2, 3}}, 2);
  testNumberOfComponents(4, {{0, 3}, {2, 3}}, 2);
  testNumberOfComponents(4, {{0, 3}, {2, 3}, {0, 2}}, 2);
  testNumberOfComponents(4, {{0, 3}, {2, 3}, {1, 3}}, 1);
  testRandomGraph(15, 0.0);
  testRandomGraph(15, 0.01);
  testRandomGraph(15, 0.05);
  testRandomGraph(15, 0.1);
  testRandomGraph(15, 0.15);
}
