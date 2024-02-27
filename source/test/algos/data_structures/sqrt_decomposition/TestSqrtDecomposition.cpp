#include <gmock/gmock.h>

#include <random>
#include <vector>

#include "./../../../../algos/data_structures/fenwick/fenwick_naive.h"
#include "./../../../../algos/data_structures/sqrt_decomposition/sqrt_decomposition_sum.h"

namespace
{
template <typename T>
void testSqrtDecomposition(std::vector<T> init,
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
      // f.increase(l, r, val);
      // fNaive.increase(l, r, val);
    }
  }
}

template <typename T>
void testSqrtDecomposition(size_t n, std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, T>> commands,
                           std::vector<T> expected)
{
  testSqrtDecomposition(std::vector<T>(n), commands, expected);
}

/* template <typename T>
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

TEST(SqrtDecomposition, TestSqrtDecompositionSum)
{
/*   testSqrtDecomposition<int>(0, {}, {});
  testSqrtDecomposition<int>(std::vector<int>(), {}, {});
  testSqrtDecomposition<int>(1, {}, {});
  testSqrtDecomposition<int>(1, {{{0, {0, 0}}, 0}}, {0});
  testSqrtDecomposition<int>(1, {{{0, {0, 0}}, 0}, {{0, {0, 0}}, 0}, {{1, {0, 0}}, 5}, {{0, {0, 0}}, 0}}, {0, 0, 5});
  testSqrtDecomposition<int>(5, {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, -5}, {{0, {0, 4}}, 0}}, {19});
  testSqrtDecomposition<size_t>(std::vector<size_t>{4, 3, 2, 2, 1},
                                {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 4}}, 0}}, {37});
  testSqrtDecomposition<size_t>(
      std::vector<size_t>{4, 3, 2, 2, 1},
      {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}}, {10, 6});
  testSqrtDecomposition<size_t>(
      std::vector<size_t>{4, 3, 2, 2, 1},
      {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {4, 4}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}}, {9, 7}); */
  testSqrtDecomposition<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {0, 0}}, 0}}, {6});
  testSqrtDecomposition<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {1, 1}}, 0}}, {5});
  testSqrtDecomposition<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {2, 2}}, 0}}, {4});
  testSqrtDecomposition<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {3, 3}}, 0}}, {3});
  testSqrtDecomposition<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {4, 4}}, 0}}, {2});
  testSqrtDecomposition<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {5, 5}}, 0}}, {1});
  testSqrtDecomposition<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {0, 5}}, 0}}, {21});
  testSqrtDecomposition<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {0, 3}}, 0}}, {18});
  testSqrtDecomposition<size_t>(std::vector<size_t>{6, 5, 4, 3, 2, 1}, {{{0, {3, 5}}, 0}}, {6});

/*   for (size_t n = 2; n < 20; ++n) {
    std::vector<int> v(n);
    std::iota(std::begin(v), std::end(v), 1);
    testRandomCommands<int>(n, 100);
    testRandomCommands<int>(v, 100);
  } */
}
