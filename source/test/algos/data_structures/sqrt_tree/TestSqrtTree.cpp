#include <gmock/gmock.h>

#include <functional>
#include <limits>
#include <random>
#include <vector>

#include "./../../../../algos/data_structures/segment_tree/segment_tree_naive.h"
#include "./../../../../algos/data_structures/sqrt_tree/sqrt_tree.h"

namespace
{
using SQT = SqrtTree<int>;
using STN = SegmentTreeNaive<int, int>;

SQT createSumSqrtTree(const std::vector<int>& init)
{
  std::function<int(int, int)> op = [](int a, int b) { return a + b; };
  return SQT(init, std::move(op));
}

SQT createMaxSqrtTree(const std::vector<int>& init)
{
  std::function<int(int, int)> op = [](int a, int b) { return std::max(a, b); };
  return SQT(init, std::move(op));
}

STN createSumNaiveSegmentTree(const std::vector<int>& init)
{
  std::function<int(size_t, size_t, const std::vector<int>&)> queryImpl = [](size_t l, size_t r,
                                                                             const std::vector<int>& a) {
    int sum = 0;
    for (size_t i = l; i <= r; ++i) {
      sum += a[i];
    }
    return sum;
  };
  std::function<int(int, int)> modifyImpl = [](int /*oldValue*/, int newValue) { return newValue; };
  return STN(init, std::move(queryImpl), std::move(modifyImpl));
}

STN createMaxNaiveSegmentTree(const std::vector<int>& init)
{
  std::function<int(size_t, size_t, const std::vector<int>&)> queryImpl = [](size_t l, size_t r,
                                                                             const std::vector<int>& a) {
    int maxValue = a[l];
    for (size_t i = l + 1; i <= r; ++i) {
      if (a[i] > maxValue) {
        maxValue = a[i];
      }
    }
    return maxValue;
  };
  std::function<int(int, int)> modifyImpl = [](int /*oldValue*/, int newValue) { return newValue; };
  return STN(init, std::move(queryImpl), std::move(modifyImpl));
}

std::pair<SQT, STN> createTrees(int c, const std::vector<int>& init)
{
  if (c == 0) {
    return {createSumSqrtTree(init), createSumNaiveSegmentTree(init)};
  } else {
    return {createMaxSqrtTree(init), createMaxNaiveSegmentTree(init)};
  }
}

void testSqrtTree(std::vector<int> init,
                  std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, int>> commands,
                  std::vector<int> expected)
{
  auto [sqt, stn] = createTrees(0, init);
  size_t idx = 0;
  for (const auto& [c, val] : commands) {
    const auto& [commandType, interval] = c;
    const auto& [l, r] = interval;
    if (commandType == 0) {
      auto q = sqt.query(l, r);
      auto qNaive = stn.query(l, r);
      EXPECT_EQ(q, expected[idx]);
      EXPECT_EQ(qNaive, expected[idx]);
      ++idx;
    }
    if (commandType == 1) {
      sqt.update(l, val);
      stn.modify(l, l, val);
    }
  }
}

void testSqrtTree(size_t n, std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, int>> commands,
                  std::vector<int> expected)
{
  testSqrtTree(std::vector<int>(n), commands, expected);
}

void testRandomCommands(std::vector<int> init, size_t steps)
{
  size_t n = init.size();
  std::mt19937 e;
  for (int c = 0; c < 2; ++c) {
    auto [st, stn] = createTrees(c, init);
    for (size_t idx = 0; idx < steps; ++idx) {
      size_t type = e() % 2;
      size_t l = e() % n;
      size_t r = e() % n;
      if (r < l) {
        std::swap(l, r);
      }
      int val = e() % 100;
      if (type == 0 || c == 3) {
        int result = st.query(l, r);
        int resultNaive = stn.query(l, r);
        EXPECT_EQ(result, resultNaive);
      } else {
        st.update(l, val);
        stn.modify(l, l, val);
      }
    }
  }
}

void testRandomCommands(size_t n, size_t steps) { testRandomCommands(std::vector<int>(n), steps); }
}  // namespace

TEST(SqrtTree, TestSqrtTree)
{
  testSqrtTree(0, {}, {});
  testSqrtTree(std::vector<int>(), {}, {});
  testSqrtTree(1, {}, {});
  testSqrtTree(1, {{{0, {0, 0}}, 0}}, {0});
  testSqrtTree(1, {{{0, {0, 0}}, 0}, {{0, {0, 0}}, 0}, {{1, {0, 0}}, 5}, {{0, {0, 0}}, 0}}, {0, 0, 5});
  testSqrtTree(5, {{{1, {1, 3}}, 3}, {{0, {0, 4}}, 0}}, {3});
  testSqrtTree(5, {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{0, {0, 4}}, 0}}, {8});
  testSqrtTree(5, {{{1, {0, 0}}, -5}, {{0, {0, 4}}, 0}}, {-5});
  testSqrtTree(5, {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, -5}, {{0, {0, 4}}, 0}}, {-2});
  testSqrtTree(std::vector<int>{4, 3, 2, 2, 1},
               {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 4}}, 0}}, {9});
  testSqrtTree(std::vector<int>{4, 3, 2, 2, 1},
               {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}}, {1, 3});
  testSqrtTree(std::vector<int>{4, 3, 2, 2, 1},
               {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {4, 4}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}}, {5, 3});
  testSqrtTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {0, 0}}, 0}}, {6});
  testSqrtTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {1, 1}}, 0}}, {5});
  testSqrtTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {2, 2}}, 0}}, {4});
  testSqrtTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {3, 3}}, 0}}, {3});
  testSqrtTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {4, 4}}, 0}}, {2});
  testSqrtTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {5, 5}}, 0}}, {1});
  testSqrtTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {0, 5}}, 0}}, {21});
  testSqrtTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {0, 3}}, 0}}, {18});
  testSqrtTree(std::vector<int>{6, 5, 4, 3, 2, 1}, {{{0, {3, 5}}, 0}}, {6});

  for (size_t n = 2; n < 75; ++n) {
    std::vector<int> v(n);
    std::iota(std::begin(v), std::end(v), 1);
    testRandomCommands(n, 100);
    testRandomCommands(v, 100);
  }
}
