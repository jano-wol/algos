#ifndef APPLICATIONS_DATA_STRUCTURES_MAXIMUM_RANGE_SUM_QUERY_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_MAXIMUM_RANGE_SUM_QUERY_INCLUDED

#include <algorithm>
#include <iostream>
#include <vector>

namespace
{
void checkMaximumRangeSumQuery(size_t l, size_t r, size_t n)
{
  if (r < l) {
    throw std::overflow_error("invalid query: r < l");
  }
  if (n <= r) {
    throw std::overflow_error("invalid query: n <= r");
  }
}

template <typename T>
T getMaximumRangeSumNaive(const std::vector<T>& a)
{
  T ret = 0;
  for (size_t i = 0; i < a.size(); ++i) {
    for (size_t j = i; j < a.size(); ++j) {
      T curr = 0;
      for (size_t k = i; k <= j; ++k) {
        curr += a[k];
      }
      if (curr > ret) {
        ret = curr;
      }
    }
  }
  return ret;
}
}  // namespace

template <typename T>
std::vector<T> maximumRangeSumQueryNaive(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [l, r] : queries) {
    checkMaximumRangeSumQuery(l, r, n);
    std::vector<T> currVec(a.begin() + l, a.begin() + r + 1);
    ret.push_back(getMaximumRangeSumNaive(currVec));
  }
  return ret;
}
#endif  // APPLICATIONS_DATA_STRUCTURES_MAXIMUM_RANGE_SUM_QUERY_INCLUDED
