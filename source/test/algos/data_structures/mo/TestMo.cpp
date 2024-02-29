#include <gmock/gmock.h>

#include <random>
#include <vector>

#include "./../../../../algos/data_structures/mo/mo.h"

namespace
{
template <typename T, typename R>
class MoObjectCount : public IMoObject<R>
{
public:
  MoObjectCount(std::vector<T> base_) : n(base_.size()), sum(0), count(0) {}

  void add(size_t /*idx*/) override { count++; };
  void remove(size_t /*idx*/) override { count++; };
  R solve() const override
  {
    count++;
    return sum;
  };
  size_t getN() const override { return n; };

  size_t getCount() const { return count; }

private:
  size_t n;
  R sum;
  mutable size_t count;
};

template <typename T>
size_t measureMoRandomQuries(size_t n, size_t m)
{
  std::vector<std::pair<size_t, size_t>> queries;
  queries.reserve(m);
  std::mt19937 e;
  for (size_t idx = 0; idx < m; ++idx) {
    size_t l = e() % n;
    size_t r = e() % n;
    if (r < l) {
      std::swap(l, r);
    }
    queries.push_back({l, r});
  }
  std::unique_ptr<IMoObject<T>> iMoObjectPtr = std::make_unique<MoObjectCount<T, T>>(std::vector<T>(n));
  Mo<T> mo(std::move(iMoObjectPtr));
  mo.solve(queries);
  const auto& o = dynamic_cast<const MoObjectCount<T, T>&>(*(mo.getMoObjectPtr()));
  return o.getCount();
}
}  // namespace

TEST(Mo, TestMo)
{
  EXPECT_EQ(measureMoRandomQuries<int>(0, 0), 0);
  EXPECT_EQ(measureMoRandomQuries<int>(1, 0), 0);
  EXPECT_EQ(measureMoRandomQuries<int>(1, 1), 2);
  EXPECT_EQ(measureMoRandomQuries<int>(1, 2), 3);
  EXPECT_EQ(measureMoRandomQuries<size_t>(1, 3), 4);
  EXPECT_EQ(measureMoRandomQuries<int>(2, 0), 0);
  EXPECT_EQ(measureMoRandomQuries<int>(100, 100), 1096);
}
