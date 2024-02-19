#include <gmock/gmock.h>

#include <random>
#include <set>
#include <vector>

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union.h"

namespace
{
size_t numberOfComponents(const DisjointSetUnion& d)
{
  const auto& parent = d.getParent();
  size_t ret = 0;
  for (size_t idx = 0; idx < d.getN(); ++idx) {
    if (idx == parent.at(idx)) {
      ++ret;
    }
  }
  return ret;
}

void testNumberOfComponents(size_t n, std::vector<std::pair<size_t, size_t>> connections, size_t expected)
{
  DisjointSetUnion d(n);
  for (const auto& [a, b] : connections) {
    d.unionSets(a, b);
  }
  EXPECT_EQ(numberOfComponents(d), expected);
}

size_t calcComponents(size_t n, const std::vector<std::pair<size_t, size_t>>& edges)
{
  size_t ret = 0;
  std::vector<bool> visited(n, false);
  std::vector<std::vector<int>> adj(n);
  for (const auto& [x, y] : edges) {
    if (x != y) {
      adj[x].push_back(y);
      adj[y].push_back(x);
    } else {
      adj[x].push_back(x);
    }
  }

  for (size_t i = 0; i < n; ++i) {
    if (visited[i] == true) {
      continue;
    }
    ++ret;
    std::set<size_t> curr;
    curr.insert(i);
    while (!curr.empty()) {
      std::set<size_t> next;
      for (auto c : curr) {
        visited[c] = true;
        for (auto x : adj[c]) {
          if ((visited[x] == false) && (curr.count(x) == 0)) {
            next.insert(x);
          }
        }
      }
      curr = next;
    }
  }
  return ret;
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
  EXPECT_EQ(numberOfComponents(d), calcComponents(n, edges));
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
