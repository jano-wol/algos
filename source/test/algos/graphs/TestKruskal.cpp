#include <gmock/gmock.h>

#include <vector>

#include "./../../../algos/graphs/kruskal/kruskal.h"

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
  testKruskal<int>(0, {}, {});
}
