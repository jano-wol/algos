#include <gmock/gmock.h>

#include <random>
#include <vector>

#include "./../../../algos/data_structures/minimum_stack/minimum_stack.h"

namespace
{
template <typename T>
void checkAlignment(const MinimumStack<T>& s, const std::vector<T>& v)
{
  EXPECT_EQ(s.size(), v.size());
  EXPECT_EQ(s.empty(), v.empty());
  if (!s.empty()) {
    EXPECT_EQ(s.getMinimum(), *std::min_element(v.begin(), v.end()));
    EXPECT_EQ(s.top(), v.back());
  }
}

template <typename T>
void simulateDataUsage(size_t steps, uint64_t seed)
{
  std::mt19937 e(seed);
  MinimumStack<T> s;
  std::vector<T> v;

  for (size_t i = 0; i < steps; ++i) {
    checkAlignment<T>(s, v);
    int type = v.empty() ? 0 : (e() % 2);
    if (type == 0) {
      T val = e() % 100;
      s.push(val);
      v.push_back(val);
    } else {
      s.pop();
      v.pop_back();
    }
  }
}
}  // namespace

TEST(MinimumStack, TestMinimumStack)
{
  simulateDataUsage<int>(0, 1);
  simulateDataUsage<int>(1, 1);
  simulateDataUsage<int>(10, 2);
  simulateDataUsage<int>(100, 3);
  simulateDataUsage<int>(1000, 4);
  simulateDataUsage<int>(3000, 5);
}
