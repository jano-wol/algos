#include <gmock/gmock.h>

#include <functional>
#include <random>
#include <vector>

#include "./../../../../algos/data_structures/segment_tree/segment_tree.h"
#include "./../../../../algos/data_structures/segment_tree/segment_tree_naive.h"

namespace
{
using ST = SegmentTree<int, int, int>;
using STN = SegmentTreeNaive<int, int>;
using Node = ST::SegmentTreeNode;

std::pair<ST, STN> createSegmentTrees(std::vector<int> init)
{
  std::function<Node(size_t, size_t, int)> createSimpleNode = [](size_t l, size_t r, int x) {
    return Node{l, r, x, std::nullopt};
  };
  std::function<Node(size_t, size_t, const Node&, const Node&)> createCompositeNode =
      [](size_t l, size_t r, const Node& ln, const Node& rn) {
        return Node{l, r, ln.treeValue + rn.treeValue, std::nullopt};
      };
  std::function<int(const Node&)> answerSimpleNode = [](const Node& l) { return l.treeValue; };
  std::function<int(int, int)> answerCompositeNode = [](int l, int r) { return l + r; };
  std::function<void(Node&, int)> modifyNode = [](Node& l, int v) { l.treeValue += (l.r - l.l + 1) * v; };
  std::function<int(int, int)> cumulateMod = [](int oldValue, int newValue) { return oldValue + newValue; };
  std::function<int(size_t, size_t, const std::vector<int>&)> queryImpl = [](size_t l, size_t r,
                                                                             const std::vector<int>& a) {
    int sum = 0;
    for (size_t i = l; i <= r; ++i) {
      sum += a[i];
    }
    return sum;
  };
  std::function<int(int, int)> modifyImpl = [](int oldValue, int newValue) { return oldValue + newValue; };

  return {
      ST(init, createSimpleNode, createCompositeNode, answerSimpleNode, answerCompositeNode, modifyNode, cumulateMod),
      STN(init, queryImpl, modifyImpl)};
}

void testSegmentTree(std::vector<int> init,
                     std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, int>> commands,
                     std::vector<int> expected)
{
  auto [st, stn] = createSegmentTrees(init);
  size_t idx = 0;
  for (const auto& [c, val] : commands) {
    const auto& [commandType, interval] = c;
    const auto& [l, r] = interval;
    if (commandType == 0) {
      auto q = st.query(l, r);
      auto qNaive = stn.query(l, r);
      EXPECT_EQ(q, expected[idx]);
      EXPECT_EQ(qNaive, expected[idx]);
      ++idx;
    }
    if (commandType == 1) {
      st.modify(l, r, val);
      stn.modify(l, r, val);
    }
  }
}

void testSegmentTree(size_t n, std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, int>> commands,
                     std::vector<int> expected)
{
  testSegmentTree(std::vector<int>(n), commands, expected);
}

void testRandomCommands(std::vector<int> init, size_t steps)
{
  size_t n = init.size();
  std::mt19937 e;
  auto [st, stn] = createSegmentTrees(init);
  for (size_t idx = 0; idx < steps; ++idx) {
    size_t type = e() % 2;
    size_t l = e() % n;
    size_t r = e() % n;
    if (r < l) {
      std::swap(l, r);
    }
    int val = e() % 100;
    if (type == 0) {
      int result = st.query(l, r);
      int resultNaive = stn.query(l, r);
      EXPECT_EQ(result, resultNaive);
    } else {
      st.modify(l, r, val);
      stn.modify(l, r, val);
    }
  }
}

void testRandomCommands(size_t n, size_t steps) { testRandomCommands(std::vector<int>(n), steps); }
}  // namespace

TEST(SegmentTree, TestSegmentTree)
{
  testSegmentTree(0, {}, {});
  testSegmentTree(std::vector<int>(), {}, {});
  testSegmentTree(1, {}, {});
  testSegmentTree(1, {{{0, {0, 0}}, 0}}, {0});
  testSegmentTree(1, {{{0, {0, 0}}, 0}, {{0, {0, 0}}, 0}, {{1, {0, 0}}, 5}, {{0, {0, 0}}, 0}}, {0, 0, 5});
  testSegmentTree(5, {{{1, {1, 3}}, 3}, {{0, {0, 4}}, 0}}, {9});
  testSegmentTree(5, {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{0, {0, 4}}, 0}}, {24});
  testSegmentTree(5, {{{1, {0, 0}}, -5}, {{0, {0, 4}}, 0}}, {-5});
  testSegmentTree(5, {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, -5}, {{0, {0, 4}}, 0}}, {19});
  testSegmentTree(std::vector<int>{4, 3, 2, 2, 1},
                  {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 4}}, 0}}, {37});
  testSegmentTree(std::vector<int>{4, 3, 2, 2, 1},
                  {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}}, {10, 6});
  testSegmentTree(std::vector<int>{4, 3, 2, 2, 1},
                  {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {4, 4}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}}, {9, 7});
  testSegmentTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {0, 0}}, 0}}, {6});
  testSegmentTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {1, 1}}, 0}}, {5});
  testSegmentTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {2, 2}}, 0}}, {4});
  testSegmentTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {3, 3}}, 0}}, {3});
  testSegmentTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {4, 4}}, 0}}, {2});
  testSegmentTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {5, 5}}, 0}}, {1});
  testSegmentTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {0, 5}}, 0}}, {21});
  testSegmentTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {0, 3}}, 0}}, {18});
  testSegmentTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {3, 5}}, 0}}, {6});

  for (size_t n = 2; n < 75; ++n) {
    std::vector<int> v(n);
    std::iota(std::begin(v), std::end(v), 1);
    testRandomCommands(n, 100);
    testRandomCommands(v, 100);
  }
}
