#include <gmock/gmock.h>

#include <random>
#include <vector>

#include "./../../../../algos/data_structures/link_cut_tree/link_cut_tree.h"
#include "./../../../../algos/data_structures/link_cut_tree/link_cut_tree_naive.h"

namespace
{
void testLinkCutTree(int n, std::vector<std::pair<int, std::pair<int, int>>> commands, std::vector<bool> expected)
{
  LinkCutTree tree(n);
  LinkCutTreeNaive treeNaive(n);
  int expectedIdx = 0;
  for (const auto& [command, p] : commands) {
    const auto& [u, v] = p;
    if (command == 0) {
      tree.link(u, v);
      treeNaive.link(u, v);
    }
    if (command == 1) {
      tree.cut(u, v);
      treeNaive.cut(u, v);
    }
    if (command == 2) {
      auto res = tree.connected(u, v);
      auto resNaive = treeNaive.connected(u, v);
      EXPECT_EQ(res, expected[expectedIdx]);
      EXPECT_EQ(resNaive, expected[expectedIdx]);
      ++expectedIdx;
    }
  }
}

void testRandomCommands(int n, int steps)
{
  std::mt19937 e;
  LinkCutTree::CPtr tree = std::make_unique<LinkCutTree>(n);
  LinkCutTreeNaive treeNaive(n);
  std::vector<std::unordered_set<int>> adj(n);
  for (int idx = 0; idx < steps; ++idx) {
    int u = e() % n;
    int v = e() % n;
    bool res = tree->connected(u, v);
    bool resNaive = treeNaive.connected(u, v);
    EXPECT_EQ(res, resNaive);
    if (adj[u].count(v) == 0 && res == false) {
      tree->link(u, v);
      treeNaive.link(u, v);
      adj[u].insert(v);
      adj[v].insert(u);
      continue;
    }
    if (adj[u].count(v) == 1) {
      tree->cut(u, v);
      treeNaive.cut(u, v);
      adj[u].erase(v);
      adj[v].erase(u);
    }
    tree = tree->clone();
  }
}
}  // namespace

TEST(LinkCutTree, TestLinkCutTree)
{
  testLinkCutTree(0, {}, {});
  testLinkCutTree(1, {}, {});
  testLinkCutTree(2, {}, {});
  testLinkCutTree(2, {{2, {0, 1}}}, {false});
  testLinkCutTree(2, {{0, {0, 1}}, {2, {0, 1}}}, {true});
  testLinkCutTree(2, {{2, {0, 1}}, {0, {0, 1}}, {2, {0, 1}}}, {false, true});
  testLinkCutTree(2, {{2, {0, 1}}, {0, {0, 1}}, {2, {0, 1}}, {1, {0, 1}}}, {false, true});
  testLinkCutTree(2, {{2, {0, 1}}, {0, {0, 1}}, {2, {0, 1}}, {1, {0, 1}}, {2, {0, 1}}}, {false, true, false});
  testLinkCutTree(
      2, {{2, {0, 1}}, {0, {0, 1}}, {2, {0, 1}}, {1, {0, 1}}, {2, {0, 1}}, {2, {0, 1}}, {0, {0, 1}}, {2, {0, 1}}},
      {false, true, false, false, true});
  testLinkCutTree(
      2, {{2, {0, 1}}, {0, {1, 0}}, {2, {0, 1}}, {1, {0, 1}}, {2, {0, 1}}, {2, {0, 1}}, {0, {0, 1}}, {2, {1, 0}}},
      {false, true, false, false, true});
  testLinkCutTree(4,
                  {{2, {0, 1}},
                   {0, {1, 0}},
                   {2, {0, 1}},
                   {0, {2, 3}},
                   {2, {0, 2}},
                   {2, {0, 3}},
                   {2, {2, 3}},
                   {0, {3, 1}},
                   {2, {3, 0}},
                   {2, {2, 0}},
                   {1, {2, 3}},
                   {2, {2, 0}},
                   {2, {1, 3}}},
                  {false, true, false, false, true, true, true, false, true});

  for (int n = 2; n < 20; ++n) {
    testRandomCommands(n, 2000);
  }
}
