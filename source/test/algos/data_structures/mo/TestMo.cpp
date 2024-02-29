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
  MoObjectCount(std::vector<T> /*base_*/) : sum(0), count(0) {}

  void add(size_t /*idx*/) override { count++; };
  void remove(size_t /*idx*/) override { count++; };
  R solve() const override
  {
    count++;
    return sum;
  };

  size_t getCount() const { return count; }

private:
  R sum;
  mutable size_t count;
};

/* template <typename T>
void testMo(std::vector<T> init, std::vector<std::pair<size_t, size_t>> queries, size_t expectedAdjusts)
{} */

template <typename T>
void measureMoRandomQuries(size_t n, size_t m)
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
  std::cout << "n=" << n << " m=" << m << " count=" << o.getCount() << "\n";
}
}  // namespace

TEST(Mo, TestMo)
{
  measureMoRandomQuries<int>(100, 100);
  measureMoRandomQuries<int>(1000, 1000);
}
