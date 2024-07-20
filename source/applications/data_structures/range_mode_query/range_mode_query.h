#ifndef APPLICATIONS_DATA_STRUCTURES_RANGE_MODE_QUERY_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_RANGE_MODE_QUERY_INCLUDED

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <vector>

#include "./../../../algos/data_structures/mo/mo.h"

namespace algos::maximum_range_mode_query_utils
{
void checkModeQuery(size_t l, size_t r, size_t n)
{
  if (r < l) {
    throw std::out_of_range("invalid query: r < l");
  }
  if (n <= r) {
    throw std::out_of_range("invalid query: n <= r");
  }
}

template <typename T>
T getMode(std::vector<T> v)
{
  std::sort(v.begin(), v.end());
  T currVal = v[0];
  size_t currFreq = 1;
  size_t maxFreq = 0;
  T mode = 0;
  for (size_t idx = 1; idx < v.size(); ++idx) {
    if (v[idx] == currVal) {
      currFreq++;
    } else {
      if (currFreq > maxFreq) {
        maxFreq = currFreq;
        mode = currVal;
        currVal = v[idx];
        currFreq = 1;
      }
    }
  }
  if (currFreq > maxFreq) {
    maxFreq = currFreq;
    mode = currVal;
  }
  return mode;
}

template <typename T, typename R>
class MoObjectMode : public IMoObject<R>
{
public:
  MoObjectMode(std::vector<T> base_) : base(std::move(base_)) {}

  void add(size_t idx) override
  {
    T val = base[idx];
    auto it = counter.find(val);
    if (it == counter.end()) {
      counter[val] = 1;
      occurance.insert({1, val});
    } else {
      auto it2 = occurance.find({it->second, val});
      occurance.erase(it2);
      ++(it->second);
      occurance.insert({it->second, val});
    }
  };

  void remove(size_t idx) override
  {
    T val = base[idx];
    auto it = counter.find(val);
    auto it2 = occurance.find({it->second, val});
    occurance.erase(it2);
    if (it->second == 1) {
      counter.erase(it);
    } else {
      --it->second;
      occurance.insert({it->second, val});
    }
  }
  R solve() const override { return occurance.begin()->second; }
  size_t getN() const override { return base.size(); }

private:
  struct cmpStruct
  {
    bool operator()(const std::pair<size_t, T>& lhs, const std::pair<size_t, T>& rhs) const
    {
      if (lhs.first < rhs.first) {
        return false;
      }
      if (lhs.first == rhs.first) {
        if (lhs.second >= rhs.second) {
          return false;
        }
      }
      return true;
    }
  };

  std::map<T, size_t> counter;
  std::set<std::pair<size_t, T>, cmpStruct> occurance;
  std::vector<T> base;
};
}  // namespace algos::maximum_range_mode_query_utils

template <typename T>
std::vector<T> rangeModeQueryNaive(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [l, r] : queries) {
    algos::maximum_range_mode_query_utils::checkModeQuery(l, r, n);
    std::vector<T> currVec(a.begin() + l, a.begin() + r + 1);
    T mode = algos::maximum_range_mode_query_utils::getMode(currVec);
    ret.push_back(mode);
  }
  return ret;
}

// runtime = O(n * log(n) * sqrt(m) + m * log(m)), memory = O(n + m), where n = |a|, m = |queries|.
template <typename T>
std::vector<T> rangeModeQueryMo(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  std::unique_ptr<IMoObject<T>> iMoObjectPtr =
      std::make_unique<algos::maximum_range_mode_query_utils::MoObjectMode<T, T>>(a);
  Mo<T> mo(std::move(iMoObjectPtr));
  return mo.solve(queries);
}

#endif  // APPLICATIONS_DATA_STRUCTURES_RANGE_MODE_QUERY_INCLUDED
