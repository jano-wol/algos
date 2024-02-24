#include <gmock/gmock.h>

#include "./../../../../algos/graphs/bfs/bfs.h"
#include "./../../../../applications/graphs/number_of_components/number_of_components.h"

namespace
{
void testPath(Graph g, size_t source, size_t target, std::vector<size_t> expected)
{
  BFS bfs(std::move(g));
  auto structure = bfs.getComponent(source);
  EXPECT_EQ(*(bfs.getPathFromSource(target, structure)), expected);
  EXPECT_EQ(*(bfs.getDistanceFromSource(target, structure)), expected.size() - 1);
}
}  // namespace

TEST(BFS, TestBFS)
{
  testPath({1, {}}, 0, 0, {0});
  testPath({1, {{0, 0}}}, 0, 0, {0});
  testPath({2, {{0, 1}}}, 0, 0, {0});
  testPath({2, {{0, 1}}}, 1, 0, {1, 0});
  testPath({2, {{0, 1}, {0, 1}}}, 1, 0, {1, 0});
  testPath({4, {{0, 1}, {2, 3}}}, 2, 3, {2, 3});
  testPath({4, {{0, 1}, {2, 3}}}, 1, 0, {1, 0});
  testPath({4, {{0, 1}, {2, 3}}}, 2, 2, {2});
  testPath({4, {{0, 1}, {2, 3}}}, 0, 0, {0});
  testPath({5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}}}, 1, 4, {1, 2, 3, 4});
  testPath({5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}}}, 1, 0, {1, 0});
  testPath({5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}}}, 1, 1, {1});
  testPath({5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}}}, 1, 0, {1, 0});
  testPath({5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}}}, 1, 4, {1, 0, 4});
  testPath({5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}}}, 1, 3, {1, 2, 3});
  testPath({5, {{0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}}}, 1, 2, {1, 2});
}
