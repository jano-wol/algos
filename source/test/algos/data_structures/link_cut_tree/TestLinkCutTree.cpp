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
/*
template <typename T>
void testFenwick(size_t n, std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, T>> commands,
                 std::vector<T> expected)
{
  testFenwick(std::vector<T>(n), commands, expected);
}

template <typename T>
void testRandomCommands(std::vector<T> init, size_t steps)
{
  size_t n = init.size();
  std::mt19937 e;
  Fenwick<T> f(init);
  FenwickNaive<T> fNaive(init);
  for (size_t idx = 0; idx < steps; ++idx) {
    size_t type = e() % 2;
    size_t l = e() % n;
    size_t r = e() % n;
    if (r < l) {
      std::swap(l, r);
    }
    T val = e() % 100;
    if (type == 0) {
      T result = f.sum(l, r);
      T resultNaive = fNaive.sum(l, r);
      EXPECT_EQ(result, resultNaive);
    } else {
      f.increase(l, r, val);
      fNaive.increase(l, r, val);
    }
  }
}

template <typename T>
void testRandomCommands(size_t n, size_t steps)
{
  testRandomCommands(std::vector<T>(n), steps);
} */
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
  /*  testFenwick<int>(0, {}, {});
    testFenwick<int>(std::vector<int>(), {}, {});
    testFenwick<int>(1, {}, {});
    testFenwick<int>(1, {{{0, {0, 0}}, 0}}, {0});
    testFenwick<int>(1, {{{0, {0, 0}}, 0}, {{0, {0, 0}}, 0}, {{1, {0, 0}}, 5}, {{0, {0, 0}}, 0}}, {0, 0, 5});
    testFenwick<int>(5, {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, -5}, {{0, {0, 4}}, 0}}, {19});
    testFenwick<size_t>(std::vector<size_t>{4, 3, 2, 2, 1},
                        {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 4}}, 0}}, {37});
    testFenwick<size_t>(std::vector<size_t>{4, 3, 2, 2, 1},
                        {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}},
                        {10, 6});
    testFenwick<size_t>(std::vector<size_t>{4, 3, 2, 2, 1},
                        {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {4, 4}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}},
                        {9, 7});
    testFenwick<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {0, 0}}, 0}}, {6});
    testFenwick<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {1, 1}}, 0}}, {5});
    testFenwick<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {2, 2}}, 0}}, {4});
    testFenwick<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {3, 3}}, 0}}, {3});
    testFenwick<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {4, 4}}, 0}}, {2});
    testFenwick<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {5, 5}}, 0}}, {1});
    testFenwick<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {0, 5}}, 0}}, {21});
    testFenwick<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {0, 3}}, 0}}, {18});
    testFenwick<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {3, 5}}, 0}}, {6});

    for (size_t n = 2; n < 20; ++n) {
      std::vector<int> v(n);
      std::iota(std::begin(v), std::end(v), 1);
      testRandomCommands<int>(n, 100);
      testRandomCommands<int>(v, 100);
    }
    */
}
