#include <gmock/gmock.h>

#include <vector>

#include "./../../../../algos/data_structures/fenwick/fenwick_naive.h"

namespace
{
template <typename T>
void testFenwick(std::vector<T> init, std::vector<std::pair<std::pair<size_t, std::pair<size_t, size_t>>, T>> commands,
                 std::vector<T> expected)
{
  FenwickNaive f(std::move(init));
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

}  // namespace

TEST(Fenwick, TestFenwick)
{
  testFenwick<int>(0, {}, {});
  testFenwick<int>(std::vector<int>(), {}, {});
  testFenwick<int>(1, {}, {});
  testFenwick<int>(1, {{{0, {0, 0}}, 0}}, {0});
  testFenwick<int>(1, {{{0, {0, 0}}, 0}, {{0, {0, 0}}, 0}, {{1, {0, 0}}, 5}, {{0, {0, 0}}, 0}}, {0, 0, 5});
  testFenwick<int>(5, {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, -5}, {{0, {0, 4}}, 0}}, {19});
  testFenwick<size_t>(std::vector<size_t>{4, 3, 2, 2, 1}, {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 4}}, 0}}, {37});
  testFenwick<size_t>(std::vector<size_t>{4, 3, 2, 2, 1}, {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {0, 0}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}}, {10, 6});
  testFenwick<size_t>(std::vector<size_t>{4, 3, 2, 2, 1}, {{{1, {1, 3}}, 3}, {{1, {0, 2}}, 5}, {{1, {4, 4}}, 1}, {{0, {0, 0}}, 0}, {{0, {3, 4}}, 0}}, {9, 7});
}
