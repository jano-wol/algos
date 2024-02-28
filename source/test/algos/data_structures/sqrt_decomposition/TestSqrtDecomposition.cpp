#include <gmock/gmock.h>

#include <random>
#include <vector>

#include "./../../../../algos/data_structures/fenwick/fenwick_naive.h"
#include "./../../../../algos/data_structures/sqrt_decomposition/sqrt_decomposition_min.h"
#include "./../../../../algos/data_structures/sqrt_decomposition/sqrt_decomposition_min_naive.h"
#include "./../../../../algos/data_structures/sqrt_decomposition/sqrt_decomposition_sum.h"

namespace
{
template <typename T>
void testSqrtDecompositionSum(std::vector<T> init,
                              std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, T>> commands,
                              std::vector<T> expected)
{
  SqrtDecompositionSum<T> d(init);
  FenwickNaive<T> fNaive(init);
  size_t idx = 0;
  for (const auto& [c, val] : commands) {
    const auto& [commandType, interval] = c;
    const auto& [l, r] = interval;
    if (commandType == 0) {
      auto sum = d.sum(l, r);
      auto sumNaive = fNaive.sum(l, r);
      EXPECT_EQ(sum, expected[idx]);
      EXPECT_EQ(sumNaive, expected[idx]);
      ++idx;
    }
    if (commandType == 1) {
      d.increase(l, r, val);
      fNaive.increase(l, r, val);
    }
  }
}

template <typename T>
void testSqrtDecompositionMin(std::vector<T> init,
                              std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, T>> commands,
                              std::vector<T> expected)
{
  SqrtDecompositionMinNaive<T> dNaive(init);
  SqrtDecompositionMin<T> d(init);
  size_t idx = 0;
  for (const auto& [c, val] : commands) {
    const auto& [commandType, interval] = c;
    const auto& [l, r] = interval;
    if (commandType == 0) {
      auto min = d.min(l, r);
      auto minNaive = dNaive.min(l, r);
      EXPECT_EQ(min, expected[idx]);
      EXPECT_EQ(minNaive, expected[idx]);
      ++idx;
    }
    if (commandType == 1) {
      d.set(l, r, val);
      dNaive.set(l, r, val);
    }
  }
}

template <typename T>
void testSqrtDecompositionSum(size_t n,
                              std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, T>> commands,
                              std::vector<T> expected)
{
  testSqrtDecompositionSum(std::vector<T>(n), commands, expected);
}

template <typename T>
void testSqrtDecompositionMin(size_t n,
                              std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, T>> commands,
                              std::vector<T> expected)
{
  testSqrtDecompositionMin(std::vector<T>(n), commands, expected);
}

template <typename T>
void testRandomCommandsSum(std::vector<T> init, size_t steps)
{
  size_t n = init.size();
  std::mt19937 e;
  SqrtDecompositionSum<T> d(init);
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
      T result = d.sum(l, r);
      T resultNaive = fNaive.sum(l, r);
      EXPECT_EQ(result, resultNaive);
    } else {
      d.increase(l, r, val);
      fNaive.increase(l, r, val);
    }
  }
}

template <typename T>
void testRandomCommandsMin(std::vector<T> init, size_t steps)
{
  size_t n = init.size();
  std::mt19937 e;
  SqrtDecompositionMinNaive<T> dNaive(init);
  SqrtDecompositionMin<T> d(init);
  for (size_t idx = 0; idx < steps; ++idx) {
    size_t type = e() % 2;
    size_t l = e() % n;
    size_t r = e() % n;
    if (r < l) {
      std::swap(l, r);
    }
    T val = e() % 100;
    if (type == 0) {
      T resultNaive = dNaive.min(l, r);
      T result = d.min(l, r);
      EXPECT_EQ(resultNaive, result);
    } else {
      dNaive.set(l, r, val);
      d.set(l, r, val);
    }
  }
}

template <typename T>
void testRandomCommandsSum(size_t n, size_t steps)
{
  testRandomCommandsSum(std::vector<T>(n), steps);
}

template <typename T>
void testRandomCommandsMin(size_t n, size_t steps)
{
  testRandomCommandsMin(std::vector<T>(n), steps);
}
}  // namespace

TEST(SqrtDecomposition, TestSqrtDecompositionSum)
{
  testSqrtDecompositionSum<int>(0, {}, {});
  testSqrtDecompositionSum<int>(std::vector<int>(), {}, {});
  testSqrtDecompositionSum<int>(1, {}, {});
  testSqrtDecompositionSum<int>(1, {{{0, {0, 0}}, 0}}, {0});
  testSqrtDecompositionSum<int>(1, {{{0, {0, 0}}, 0}, {{0, {0, 0}}, 0}, {{1, {0, 0}}, 5}, {{0, {0, 0}}, 0}}, {0, 0, 5});
  testSqrtDecompositionSum<int>(5, {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, -5}, {{0, {0, 4}}, 0}}, {19});
  testSqrtDecompositionSum<size_t>(std::vector<size_t>{4, 3, 2, 2, 1},
                                   {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 4}}, 0}}, {37});
  testSqrtDecompositionSum<size_t>(
      std::vector<size_t>{4, 3, 2, 2, 1},
      {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}}, {10, 6});
  testSqrtDecompositionSum<size_t>(
      std::vector<size_t>{4, 3, 2, 2, 1},
      {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {4, 4}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}}, {9, 7});
  testSqrtDecompositionSum<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {0, 0}}, 0}}, {6});
  testSqrtDecompositionSum<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {1, 1}}, 0}}, {5});
  testSqrtDecompositionSum<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {2, 2}}, 0}}, {4});
  testSqrtDecompositionSum<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {3, 3}}, 0}}, {3});
  testSqrtDecompositionSum<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {4, 4}}, 0}}, {2});
  testSqrtDecompositionSum<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {5, 5}}, 0}}, {1});
  testSqrtDecompositionSum<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {0, 5}}, 0}}, {21});
  testSqrtDecompositionSum<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {0, 3}}, 0}}, {18});
  testSqrtDecompositionSum<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {3, 5}}, 0}}, {6});

  for (size_t n = 2; n < 20; ++n) {
    std::vector<int> v(n);
    std::iota(std::begin(v), std::end(v), 1);
    testRandomCommandsSum<int>(n, 100);
    testRandomCommandsSum<int>(v, 100);
  }
}

TEST(SqrtDecomposition, TestSqrtDecompositionMin)
{
  testSqrtDecompositionMin<int>(0, {}, {});
  testSqrtDecompositionMin<int>(std::vector<int>(), {}, {});
  testSqrtDecompositionMin<int>(1, {}, {});
  testSqrtDecompositionMin<int>(1, {{{0, {0, 0}}, 0}}, {0});
  testSqrtDecompositionMin<int>(1, {{{0, {0, 0}}, 0}, {{0, {0, 0}}, 0}, {{1, {0, 0}}, 5}, {{0, {0, 0}}, 0}}, {0, 0, 5});
  testSqrtDecompositionMin<int>(5, {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, -5}, {{0, {0, 4}}, 0}}, {-5});
  testSqrtDecompositionMin<size_t>(std::vector<size_t>{4, 3, 2, 2, 1},
                                   {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 4}}, 0}}, {1});
  testSqrtDecompositionMin<size_t>(
      std::vector<size_t>{4, 3, 2, 2, 1},
      {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}}, {1, 1});
  testSqrtDecompositionMin<size_t>(
      std::vector<size_t>{4, 3, 2, 2, 1},
      {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {4, 4}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}}, {5, 1});
  testSqrtDecompositionMin<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {0, 0}}, 0}}, {6});
  testSqrtDecompositionMin<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {1, 1}}, 0}}, {5});
  testSqrtDecompositionMin<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {2, 2}}, 0}}, {4});
  testSqrtDecompositionMin<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {3, 3}}, 0}}, {3});
  testSqrtDecompositionMin<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {4, 4}}, 0}}, {2});
  testSqrtDecompositionMin<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {5, 5}}, 0}}, {1});
  testSqrtDecompositionMin<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {0, 5}}, 0}}, {1});
  testSqrtDecompositionMin<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {0, 3}}, 0}}, {3});
  testSqrtDecompositionMin<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {3, 5}}, 0}}, {1});
  testSqrtDecompositionMin<size_t>(std::vector<size_t>{1, 2, 3}, {{{1, {1, 1}}, 1}}, {});

  for (size_t n = 2; n < 30; ++n) {
    std::vector<int> v(n);
    std::iota(std::begin(v), std::end(v), 1);
    std::vector<int> v2 = v;
    std::reverse(v2.begin(), v2.end());
    testRandomCommandsMin<int>(n, 100);
    testRandomCommandsMin<int>(v, 100);
    testRandomCommandsMin<int>(v2, 100);
  }
}
