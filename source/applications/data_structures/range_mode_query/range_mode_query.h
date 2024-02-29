#ifndef APPLICATIONS_DATA_STRUCTURES_RANGE_MODE_QUERY_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_RANGE_MODE_QUERY_INCLUDED

#include <algorithm>
#include <memory>
#include <vector>

#include "./../../../algos/data_structures/mo/mo.h"

namespace
{
void checkModeQuery(size_t l, size_t r, size_t n)
{
  if (r < l) {
    throw std::overflow_error("invalid query: r < l");
  }
  if (n <= r) {
    throw std::overflow_error("invalid query: n <= r");
  }
}

template <typename T, typename R>
class MoObjectMode : public IMoObject<R>
{
public:
  MoObjectMode(std::vector<T> base_) : sum(0), base(std::move(base_)) {}

  void add(size_t idx) override { sum += base[idx]; };
  void remove(size_t idx) override { sum -= base[idx]; };
  R solve() const override { return sum; };
  size_t getN() const override { return base.size(); };

private:
  R sum;
  std::vector<T> base;
};
}  // namespace

template <typename T>
std::vector<T> rangeModeQueryNaive(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [l, r] : queries) {
    checkModeQuery(l, r, n);
    T sum = a[l];
    for (size_t i = l + 1; i <= r; ++i) {
      sum += a[i];
    }
    ret.push_back(sum);
  }
  return ret;
}

// runtime = O((n + m) * sqrt(n)), memory = O(n + m), where n = |a|, m = |queries|.
template <typename T>
std::vector<T> rangeModeQueryMo(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  std::unique_ptr<IMoObject<T>> iMoObjectPtr = std::make_unique<MoObjectMode<T, T>>(a);
  Mo<T> mo(std::move(iMoObjectPtr));
  return mo.solve(queries);
}

#endif  // APPLICATIONS_DATA_STRUCTURES_RANGE_MODE_QUERY_INCLUDED
