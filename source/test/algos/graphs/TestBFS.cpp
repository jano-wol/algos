#include <gmock/gmock.h>

#include <random>
#include <set>
#include <vector>

#include "./../../../algos/graphs/bfs/bfs.h"

namespace
{
std::vector<std::vector<size_t>> edgesToAdj(size_t n, std::vector<std::pair<size_t, size_t>> edges)
{
  std::vector<std::vector<size_t>> adj(n);
  for (const auto& [x, y] : edges) {
    if (x != y) {
      adj[x].push_back(y);
      adj[y].push_back(x);
    } else {
      adj[x].push_back(x);
    }
  }
  return adj;
}

void testNumberOfComponents(size_t n, std::vector<std::pair<size_t, size_t>> edges, size_t expected)
{
  auto adj = edgesToAdj(n, edges);
  BFS bfs(n, adj);
  auto components = bfs.partitiate();
  int max = -1;
  for (auto c : components) {
    if (int(c) > max) {
      max = c;
    }
  }
  int numberOfComponents = max + 1;

  EXPECT_EQ(numberOfComponents, expected);
}

size_t calcComponents(size_t n, const std::vector<std::pair<size_t, size_t>>& edges)
{
  auto adj = edgesToAdj(n, edges);

  size_t ret = 0;
  std::vector<bool> visited(n, false);
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
  std::vector<std::pair<size_t, size_t>> edges;
  std::mt19937 e;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      if (static_cast<double>(e() % 100) < p * 100.0) {
        edges.push_back({i, j});
      }
    }
  }
  testNumberOfComponents(n, edges, calcComponents(n, edges));
}
}  // namespace

TEST(BFS, TestBFS)
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
