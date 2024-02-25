#include <gmock/gmock.h>

#include <random>
#include <vector>

#include "./../../../../algos/data_structures/fenwick/fenwick.h"
#include "./../../../../algos/data_structures/fenwick/fenwick_2d_naive.h"
#include "./../../../../algos/data_structures/fenwick/fenwick_naive.h"

namespace
{
template <typename T>
void testFenwick(std::vector<T> init, std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, T>> commands,
                 std::vector<T> expected)
{
  Fenwick<T> f(init);
  FenwickNaive<T> fNaive(init);
  size_t idx = 0;
  for (const auto& [c, val] : commands) {
    const auto& [commandType, interval] = c;
    const auto& [l, r] = interval;
    if (commandType == 0) {
      auto sum = f.sum(l, r);
      auto sumNaive = fNaive.sum(l, r);
      EXPECT_EQ(sum, expected[idx]);
      EXPECT_EQ(sumNaive, expected[idx]);
      ++idx;
    }
    if (commandType == 1) {
      f.increase(l, r, val);
      fNaive.increase(l, r, val);
    }
  }
}

template <typename T>
void testFenwick(size_t n, std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, T>> commands,
                 std::vector<T> expected)
{
  testFenwick(std::vector<T>(n), commands, expected);
}

template <typename T>
void testFenwick2D(
    std::vector<std::vector<T>> init,
    std::vector<std::pair<std::pair<size_t, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>, T>>
        commands,
    std::vector<T> expected)
{
  // Fenwick<T> f(init);
  Fenwick2DNaive<T> fNaive(init);
  size_t idx = 0;
  for (const auto& [c, val] : commands) {
    const auto& [commandType, interval] = c;
    const auto& [sW, nE] = interval;
    if (commandType == 0) {
      // auto sum = f.sum(l, r);
      auto sumNaive = fNaive.sum(sW, nE);
      // EXPECT_EQ(sum, expected[idx]);
      EXPECT_EQ(sumNaive, expected[idx]);
      ++idx;
    }
    if (commandType == 1) {
      // f.increase(l, r, val);
      fNaive.increase(sW, nE, val);
    }
  }
}

template <typename T>
void testFenwick2D(
    size_t m, size_t n,
    std::vector<std::pair<std::pair<size_t, std::pair<std::pair<size_t, size_t>, std::pair<size_t, size_t>>>, T>>
        commands,
    std::vector<T> expected)
{
  testFenwick2D(std::vector<std::vector<T>>(m, std::vector<T>(n)), commands, expected);
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
}

template <typename T>
void testRandomCommands2D(std::vector<std::vector<T>> init, size_t steps)
{
  size_t m = init.size();
  size_t n = init[0].size();
  std::mt19937 e;
  // Fenwick2D<T> f(init);
  Fenwick2DNaive<T> fNaive(init);
  for (size_t idx = 0; idx < steps; ++idx) {
    size_t type = e() % 2;
    size_t s = e() % m;
    size_t no = e() % m;
    if (no < s) {
      std::swap(no, s);
    }
    size_t w = e() % n;
    size_t ea = e() % n;
    if (ea < w) {
      std::swap(w, ea);
    }
    T val = e() % 100;
    if (type == 0) {
      // T result = f.sum(l, r);
      T resultNaive = fNaive.sum({s, w}, {no, ea});
      // EXPECT_EQ(result, resultNaive);
      EXPECT_EQ(resultNaive, resultNaive);
    } else {
      // f.increase(l, r, val);
      fNaive.increase({s, w}, {no, ea}, val);
    }
  }
}

template <typename T>
void testRandomCommands2D(size_t m, size_t n, size_t steps)
{
  testRandomCommands2D(std::vector<std::vector<T>>(m, std::vector<T>(n)), steps);
}
}  // namespace

TEST(Fenwick, TestFenwick)
{
  testFenwick<int>(0, {}, {});
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
}

TEST(Fenwick2D, TestFenwick2D)
{
  testFenwick2D<int>(0, 0, {}, {});
  testFenwick2D<int>(0, 1, {}, {});
  testFenwick2D<int>(1, 0, {}, {});
  testFenwick2D<int>(1, 1, {}, {});
  testFenwick2D<int>(1, 1, {{{0, {{0, 0}, {0, 0}}}, 5}}, {0});
  testFenwick2D<int>(1, 1, {{{0, {{0, 0}, {0, 0}}}, 5}, {{1, {{0, 0}, {0, 0}}}, 5}, {{0, {{0, 0}, {0, 0}}}, 5}},
                     {0, 5});
  testFenwick2D<int>(2, 3, {{{0, {{0, 0}, {0, 0}}}, 5}, {{1, {{0, 0}, {1, 2}}}, 5}, {{0, {{0, 0}, {1, 2}}}, 0}},
                     {0, 30});
  testFenwick2D<int>(2, 3,
                     {{{0, {{0, 0}, {0, 0}}}, 5},
                      {{1, {{0, 0}, {1, 2}}}, 5},
                      {{0, {{0, 0}, {1, 2}}}, 0},
                      {{1, {{0, 0}, {0, 2}}}, 3},
                      {{0, {{0, 0}, {1, 2}}}, 0},
                      {{0, {{1, 2}, {1, 2}}}, 0},
                      {{0, {{0, 0}, {1, 1}}}, 0}},
                     {0, 30, 39, 5, 26});
  testFenwick2D<size_t>({{1, 2, 3}, {4, 5, 6}},
                        {{{0, {{0, 0}, {0, 0}}}, 5},
                         {{0, {{1, 2}, {1, 2}}}, 5},
                         {{1, {{0, 0}, {1, 2}}}, 5},
                         {{0, {{0, 0}, {1, 2}}}, 0},
                         {{1, {{0, 0}, {0, 2}}}, 3},
                         {{0, {{0, 0}, {1, 2}}}, 0},
                         {{0, {{1, 2}, {1, 2}}}, 0},
                         {{0, {{0, 0}, {1, 1}}}, 0}},
                        {1, 6, 51, 60, 11, 38});
  for (size_t m = 1; m < 10; ++m) {
    for (size_t n = 1; n < 10; ++n) {
      std::vector<int> v(n);
      std::iota(std::begin(v), std::end(v), 1);
      std::vector<std::vector<int>> mat(m, v);
      testRandomCommands2D<int>(m, n, 100);
      testRandomCommands2D<int>(mat, 100);
    }
  }
}
