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

template <typename T>
std::vector<T> getMode(std::vector<T> v)
{
  std::sort(v.begin(), v.end());
  T currVal = v[0];
  size_t currFreq = 1;
  size_t maxFreq = 0;
  std::vector<T> mode;
  for (size_t idx = 1; idx < v.size(); ++idx) {
    if (v[idx] == currVal) {
      currFreq++;
    } else {
      if (currFreq == maxFreq) {
        mode.push_back(currVal);
      }
      if (currFreq > maxFreq) {
        maxFreq = currFreq;
        mode = {currVal};
      }
      currVal = v[idx];
      currFreq = 1;
    }
  }
  if (currFreq == maxFreq) {
    mode.push_back(currVal);
  }
  if (currFreq > maxFreq) {
    maxFreq = currFreq;
    mode = {currVal};
  }
  return mode;
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
std::vector<std::vector<T>> rangeModeQueryNaive(const std::vector<T>& a,
                                                const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<std::vector<T>> ret;
  ret.reserve(queries.size());
  for (const auto& [l, r] : queries) {
    checkModeQuery(l, r, n);
    std::vector<T> currVec(a.begin() + l, a.begin() + r + 1);
    ret.emplace_back(getMode(currVec));
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
