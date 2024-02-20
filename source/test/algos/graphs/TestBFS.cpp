#include <gmock/gmock.h>

#include <random>
#include <set>
#include <vector>

#include "./../../../algos/graphs/bfs/bfs.h"
#include "./../../../applications/graphs/number_of_components/number_of_components.h"

namespace
{
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
  testNumberOfComponents(n, edges, numberOfComponentsNaive(n, edges));
}

void testPath(size_t n, std::vector<std::pair<size_t, size_t>> edges, size_t source, size_t target,
              std::vector<size_t> expected)
{
  auto adj = edgesToAdj(n, edges);
  BFS bfs(n, adj);
  auto structure = bfs.getComponent(source);
  EXPECT_EQ(*(bfs.getPathFromSource(target, structure)), expected);
  EXPECT_EQ(*(bfs.getDistanceFromSource(target, structure)), expected.size() - 1);
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
  testPath(1, {{0, 0}}, 0, 0, {0});
  testPath(4, {{0, 1}, {2, 3}}, 2, 3, {2, 3});
  testPath(4, {{0, 1}, {2, 3}}, 1, 0, {1, 0});
  testPath(4, {{0, 1}, {2, 3}}, 2, 2, {2});
  testPath(4, {{0, 1}, {2, 3}}, 0, 0, {0});
  testPath(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}}, 1, 4, {1, 2, 3, 4});
  testPath(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}}, 1, 0, {1, 0});
  testPath(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}}, 1, 1, {1});
  testPath(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}}, 1, 0, {1, 0});
  testPath(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}}, 1, 4, {1, 0, 4});
  testPath(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}}, 1, 3, {1, 2, 3});
  testPath(5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}}, 1, 2, {1, 2});
}
