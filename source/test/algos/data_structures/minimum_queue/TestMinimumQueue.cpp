#include <gmock/gmock.h>

#include <random>
#include <vector>

#include "./../../../../algos/data_structures/minimum_queue/minimum_queue.h"

namespace
{
template <typename T>
void checkAlignment(MinimumQueue<T>& q, const std::vector<T>& v)
{
  EXPECT_EQ(q.size(), v.size());
  EXPECT_EQ(q.empty(), v.empty());
  if (!q.empty()) {
    EXPECT_EQ(q.getMinimum(), *std::min_element(v.begin(), v.end()));
    EXPECT_EQ(q.top(), v[0]);
  }
}

template <typename T>
void simulateDataUsage(size_t steps, uint64_t seed)
{
  std::mt19937 e(seed);
  MinimumQueue<T> q;
  std::vector<T> v;

  for (size_t i = 0; i < steps; ++i) {
    checkAlignment<T>(q, v);
    int type = v.empty() ? 0 : (e() % 2);
    if (type == 0) {
      T val = e() % 100;
      q.push(val);
      v.push_back(val);
    } else {
      q.pop();
      v.erase(v.begin());
    }
  }
}
}  // namespace

TEST(MinimumQueue, TestMinimumQueue)
{
  simulateDataUsage<int>(0, 1);
  simulateDataUsage<int>(1, 1);
  simulateDataUsage<int>(10, 2);
  simulateDataUsage<int>(100, 3);
  simulateDataUsage<size_t>(1000, 4);
  simulateDataUsage<int>(3000, 5);
}
