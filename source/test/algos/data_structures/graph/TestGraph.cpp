#include <gmock/gmock.h>

#include <vector>

#include "./../../../../algos/data_structures/graph/graph.h"

namespace
{
void testEdgesToAdj(Graph g, const std::vector<std::vector<size_t>>& expectedAdj)
{
  auto adj = g.getAdj();
  EXPECT_EQ(adj, expectedAdj);
}

void testAdjToEdges(Graph g, const std::vector<std::pair<size_t, size_t>>& expectedEdges)
{
  auto edges = g.getEdges();
  EXPECT_EQ(edges, expectedEdges);
}
}  // namespace

TEST(Graph, TestGraph)
{
  std::vector<std::pair<size_t, size_t>> edges = std::vector<std::pair<size_t, size_t>>();
  std::vector<std::vector<size_t>> expectedAdj;
  testEdgesToAdj({0, edges}, expectedAdj);
  expectedAdj = {{}};
  testEdgesToAdj({1, edges}, expectedAdj);
  expectedAdj = {{}, {}};
  testEdgesToAdj({2, edges}, expectedAdj);
  expectedAdj = {{}, {}, {}};
  testEdgesToAdj({3, edges}, expectedAdj);
  edges = {{0, 0}};
  expectedAdj = {{0}};
  testEdgesToAdj({1, edges}, expectedAdj);
  edges = {{0, 1}};
  expectedAdj = {{1}, {0}};
  testEdgesToAdj({2, edges}, expectedAdj);
  edges = {{0, 1}, {1, 0}};
  expectedAdj = {{1, 1}, {0, 0}};
  testEdgesToAdj({2, edges}, expectedAdj);
  edges = {{0, 0}, {1, 1}};
  expectedAdj = {{0}, {1}};
  testEdgesToAdj({2, edges}, expectedAdj);
  edges = {{0, 0}, {1, 1}, {1, 1}, {0, 0}};
  expectedAdj = {{0, 0}, {1, 1}};
  testEdgesToAdj({2, edges}, expectedAdj);
  edges = {{0, 1}, {1, 0}};
  expectedAdj = {{1, 1}, {0, 0}};
  testEdgesToAdj({2, edges}, expectedAdj);
  edges = {{0, 1}, {1, 2}};
  expectedAdj = {{1}, {0, 2}, {1}};
  testEdgesToAdj({3, edges}, expectedAdj);
  edges = {{1, 2}, {0, 1}};
  expectedAdj = {{1}, {2, 0}, {1}};
  testEdgesToAdj({3, edges}, expectedAdj);
  edges = {{1, 2}, {0, 1}, {2, 0}};
  expectedAdj = {{1, 2}, {2, 0}, {1, 0}};
  testEdgesToAdj({3, edges}, expectedAdj);

  std::vector<std::vector<size_t>> adj = std::vector<std::vector<size_t>>();
  std::vector<std::pair<size_t, size_t>> expectedEdges = std::vector<std::pair<size_t, size_t>>();
  testAdjToEdges(adj, expectedEdges);
  adj = {{}};
  testAdjToEdges(adj, expectedEdges);
  adj = {{}, {}};
  testAdjToEdges(adj, expectedEdges);
  adj = {{}, {}, {}};
  testAdjToEdges(adj, expectedEdges);
  adj = {{0}};
  expectedEdges = {{0, 0}};
  testAdjToEdges(adj, expectedEdges);
  adj = {{0, 0}};
  expectedEdges = {{0, 0}, {0, 0}};
  testAdjToEdges(adj, expectedEdges);
  adj = {{1}, {0}};
  expectedEdges = {{0, 1}};
  testAdjToEdges(adj, expectedEdges);
  adj = {{0, 1}, {1, 0}};
  expectedEdges = {{0, 0}, {0, 1}, {1, 1}};
  testAdjToEdges(adj, expectedEdges);
  adj = {{1}, {0, 2}, {1}};
  expectedEdges = {{0, 1}, {1, 2}};
  testAdjToEdges(adj, expectedEdges);
  adj = {{1, 2}, {0, 2}, {1, 0}};
  expectedEdges = {{0, 1}, {0, 2}, {1, 2}};
  testAdjToEdges(adj, expectedEdges);
  adj = {{1, 2, 0}, {0, 2}, {1, 0, 1}};
  expectedEdges = {{0, 1}, {0, 2}, {0, 0}, {1, 2}};
  testAdjToEdges(adj, expectedEdges);
}
