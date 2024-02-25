#include <gmock/gmock.h>

#include <random>
#include <vector>

#include "./../../../../algos/data_structures/fenwick/fenwick_naive.h"

namespace
{
template <typename T>
void testFenwick(std::vector<T> init, std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, T>> commands,
                 std::vector<T> expected)
{
  FenwickNaive<T> f(std::move(init));
  size_t idx = 0;
  for (const auto& [c, val] : commands) {
    const auto& [commandType, interval] = c;
    const auto& [l, r] = interval;
    if (commandType == 0) {
      auto sum = f.sum(l, r);
      EXPECT_EQ(sum, expected[idx]);
      ++idx;
    }
    if (commandType == 1) {
      f.increase(l, r, val);
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
void testRandomCommands(size_t n, size_t steps)
{
  std::mt19937 e;
  FenwickNaive<T> fNaive(n);
  for (size_t idx = 0; idx < steps; ++idx) {
    size_t type = e() % 2;
    size_t l = e() % n;
    size_t r = e() % n;
    if (r < l) {
      std::swap(l, r);
    }
    T val = e() % 100;
    if (type == 0) {
      T resultNaive = fNaive.sum(l, r);
      EXPECT_EQ(resultNaive, resultNaive);
    } else {
      fNaive.increase(l, r, val);
    }
  }
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
    testRandomCommands<int>(n, 100);
  }
}
