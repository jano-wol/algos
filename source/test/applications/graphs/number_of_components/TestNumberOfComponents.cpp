#include <gmock/gmock.h>

#include <random>

#include "./../../../../applications/graphs/number_of_components/number_of_components.h"

namespace
{
void testNumberOfComponents(Graph g, size_t expected)
{
  auto resultNaive = numberOfComponentsNaive(g);
  auto resultBFS = numberOfComponentsBFS(g);
  auto resultDisjointSetUnion = numberOfComponentsDisjointSetUnion(g);
  EXPECT_EQ(resultNaive, expected);
  EXPECT_EQ(resultBFS, expected);
  EXPECT_EQ(resultDisjointSetUnion, expected);
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
  Graph g(n, edges);
  auto resultNaive = numberOfComponentsNaive(g);
  auto resultBFS = numberOfComponentsBFS(g);
  auto resultDisjointSetUnion = numberOfComponentsDisjointSetUnion(g);
  EXPECT_EQ(resultNaive, resultBFS);
  EXPECT_EQ(resultNaive, resultDisjointSetUnion);
}
}  // namespace

TEST(NumberOfComponents, TestNumberOfComponents)
{
  testNumberOfComponents({0, {}}, 0);
  testNumberOfComponents({1, {}}, 1);
  testNumberOfComponents({1, {{0, 0}}}, 1);
  testNumberOfComponents({2, {{0, 0}, {1, 1}}}, 2);
  testNumberOfComponents({2, {}}, 2);
  testNumberOfComponents({2, {{0, 1}, {0, 1}}}, 1);
  testNumberOfComponents({3, {}}, 3);
  testNumberOfComponents({3, {{0, 1}}}, 2);
  testNumberOfComponents({3, {{0, 1}, {0, 1}}}, 2);
  testNumberOfComponents({3, {{0, 1}, {0, 2}}}, 1);
  testNumberOfComponents({3, {{0, 1}, {0, 2}, {1, 2}}}, 1);
  testNumberOfComponents({4, {}}, 4);
  testNumberOfComponents({4, {{1, 3}}}, 3);
  testNumberOfComponents({4, {{0, 1}, {2, 3}}}, 2);
  testNumberOfComponents({4, {{0, 3}, {2, 3}}}, 2);
  testNumberOfComponents({4, {{0, 3}, {2, 3}, {0, 2}}}, 2);
  testNumberOfComponents({4, {{0, 3}, {2, 3}, {1, 3}}}, 1);
  testRandomGraph(15, 0.0);
  testRandomGraph(15, 0.01);
  testRandomGraph(15, 0.05);
  testRandomGraph(15, 0.1);
  testRandomGraph(15, 0.15);
}
