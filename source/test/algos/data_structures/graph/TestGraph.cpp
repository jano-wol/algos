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
  std::vector<std::pair<size_t, size_t>> edges;
  std::vector<std::vector<size_t>> adj;

  edges = std::vector<std::pair<size_t, size_t>>();
  std::vector<std::vector<size_t>> expectedAdj;
  testEdgesToAdj({0, edges}, expectedAdj);
  expectedAdj = {{}};
  testEdgesToAdj({1, edges}, expectedAdj);
  expectedAdj = {{}, {}};
  testEdgesToAdj({2, edges}, expectedAdj);
  expectedAdj = {{}, {}, {}};
  testEdgesToAdj({3, edges}, expectedAdj);
  testEdgesToAdj({3, edges}, expectedAdj);
}
