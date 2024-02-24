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

TEST(Fenwick, TestFenwick) { testFenwick<int>(0, {}, {}); }
