#include <gmock/gmock.h>
#include <random>

#include "./../../../../applications/data_structures/closest_in_range_query/closest_in_range_query.h"

namespace
{
template <typename T>
void testExpected(const std::vector<T>& a, const std::vector<std::pair<std::pair<size_t, size_t>, T>>& queries,
                  const std::vector<T>& expected)
{
  auto resultNaive = closestInRangeQueryNaive(a, queries);
  auto resultSortedTree = closestInRangeQuerySortedTree(a, queries);
  EXPECT_EQ(resultNaive, expected);
  EXPECT_EQ(resultSortedTree, expected);
}

template <typename T>
void testRandom(size_t n)
{
  std::mt19937 e;
  std::vector<T> a(n);
  std::vector<std::pair<std::pair<size_t, size_t>, T>> queries;
  for (size_t idx = 0; idx < n; ++idx) {
    a[idx] = e() % 100 - 50;
  }
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i; j < n; ++j) {
      queries.push_back({{i, j}, (T(e()) % 100 - 50)});
    }
  }
  auto resultNaive = closestInRangeQueryNaive(a, queries);
  auto resultSortedTree = closestInRangeQueryNaive(a, queries);
  EXPECT_EQ(resultNaive, resultSortedTree);
}
}  // namespace

TEST(ClosestInRange, TestClosestInRangeQuery)
{
  testExpected(std::vector<int>{}, {}, {});
  testExpected(std::vector<int>{0}, {}, {});
  testExpected(std::vector<int>{0}, {{{0, 0}, 0}}, {0});
  testExpected(std::vector<int>{0}, {{{0, 0}, {0}}, {{0, 0}, {0}}}, {0, 0});
  testExpected(std::vector<int>{7, 6, 3, 2, 4, 5, -1, -4, 3, 6, 7}, {{{5, 5}, 3}, {{2, 8}, 10}, {{4, 6}, -4}},
               {5, 5, -1});
  testExpected(std::vector<int>{7, 6, 3, 2, 4, 5, -1, -4, 3, 6, 7}, {{{3, 9}, -5}, {{0, 0}, 100}, {{8, 9}, 0}},
               {-4, 7, 3});
  testExpected(std::vector<int>{7, 6, 3, 2, 4, 5, -1, -4, 3, 6, 7}, {{{9, 10}, 100}, {{2, 3}, 5}, {{4, 6}, 1}},
               {7, 3, -1});
  testExpected(std::vector<int>{5, 4, 3, 2, 5, 4, 3, 2}, {{{0, 4}, 3}, {{2, 3}, 100}, {{4, 6}, 0}}, {3, 3, 3});
  testExpected(std::vector<int>{5, -4, -3, -2, -5, 4, -3, 2}, {{{0, 4}, 0}, {{2, 3}, 6}, {{4, 6}, -100}}, {-2, -2, -5});
  testExpected(std::vector<int>{-5, -4, -3, -2, -5, -4, -3, -2},
               {{{0, 4}, 5}, {{2, 3}, 2}, {{4, 6}, -10}, {{0, 0}, 1}, {{6, 6}, 2}, {{7, 7}, -2}, {{0, 7}, 3}},
               {-2, -2, -5, -5, -3, -2, -2});
  testExpected(std::vector<int>{-8, -4, 1, -2, 3, -2, 5, -5, 1, 3, -8, 1},
               {{{0, 11}, -1}, {{3, 11}, 1}, {{4, 11}, 6}, {{5, 11}, 0}, {{7, 10}, 8}}, {-2, 1, 5, 1, 3});
  for (size_t i = 0; i < 20; ++i) {
    testRandom<int>(i);
  }
}
