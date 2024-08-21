#include <gmock/gmock.h>

#include "./../../../../algos/graphs/kruskal/kruskal.h"

namespace
{
template <typename T>
void testKruskal(size_t n, std::vector<typename Kruskal<T>::Edge> edges, std::vector<size_t> expected)
{
  auto result = Kruskal<T>::kruskal(n, edges);
  EXPECT_EQ(result, expected);
}
}  // namespace

TEST(Kruskal, TestKruskal)
{
  testKruskal<int>(0, {}, {});
  testKruskal<int>(1, {}, {});
  testKruskal<int>(1, {{0, 0, 1}}, {});
  testKruskal<int>(1, {{0, 0, -1}}, {});
  testKruskal<int>(2, {}, {});
  testKruskal<int>(2, {{0, 0, 1}, {1, 1, -1}}, {});
  testKruskal<int>(2, {{0, 1, 1}, {0, 1, -1}}, {1});
  testKruskal<int>(2, {{0, 1, -1}, {0, 1, 1}}, {0});
  testKruskal<int>(3, {{0, 1, 1}, {1, 2, 2}, {2, 0, 0}}, {2, 0});
  testKruskal<double>(3, {{0, 1, -1.1}, {1, 2, -2.2}, {2, 0, -3.3}}, {2, 1});
  testKruskal<size_t>(
      6, {{0, 1, 2}, {0, 3, 1}, {0, 4, 4}, {1, 2, 3}, {1, 3, 3}, {1, 5, 7}, {2, 3, 5}, {2, 5, 8}, {3, 4, 9}},
      {1, 0, 3, 2, 5});
  testKruskal<int>(6,
                   {{0, 1, 13},
                    {0, 2, 28},
                    {0, 3, 8},
                    {1, 2, 27},
                    {1, 4, 39},
                    {2, 3, 2},
                    {2, 4, 34},
                    {2, 5, 14},
                    {3, 5, 7},
                    {4, 5, 36}},
                   {5, 8, 2, 0, 11116});
}
