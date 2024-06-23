#ifndef APPLICATIONS_DATA_STRUCTURES_CLOSEST_IN_RANGE_QUERY_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_CLOSEST_IN_RANGE_QUERY_INCLUDED

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "./../../../algos/data_structures/segment_tree/sorted_tree.h"

namespace
{
void checkClosestInRangeQuery(size_t l, size_t r, size_t n)
{
  if (r < l) {
    throw std::overflow_error("invalid query: r < l");
  }
  if (n <= r) {
    throw std::overflow_error("invalid query: n <= r");
  }
}

template <typename T>
T getClosestInRangeNaive(const std::vector<T>& a, T val)
{
  T ret = a[0];
  T minDiff = ((a[0] - val) < 0) ? (val - a[0]) : (a[0] - val);
  for (size_t i = 1; i < a.size(); ++i) {
    T diff = ((a[i] - val) < 0) ? (val - a[i]) : (a[i] - val);
    if (diff < minDiff) {
      minDiff = diff;
      ret = a[i];
    }
  }
  return ret;
}

/* template <typename T>
T getMaximumRangeSumDirect(const std::vector<T>& a)
{
  T ret = 0;
  T sum = 0;
  for (size_t idx = 0; idx < a.size(); ++idx) {
    sum += a[idx];
    if (sum < 0) {
      sum = 0;
    }
    if (sum > ret) {
      ret = sum;
    }
  }
  return ret;
} */
}  // namespace

template <typename T>
std::vector<T> closestInRangeQueryNaive(const std::vector<T>& a,
                                        const std::vector<std::pair<std::pair<size_t, size_t>, T>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [bounds, val] : queries) {
    const auto& [l, r] = bounds;
    checkClosestInRangeQuery(l, r, n);
    std::vector<T> currVec(a.begin() + l, a.begin() + r + 1);
    ret.push_back(getClosestInRangeNaive(currVec, val));
  }
  return ret;
}

// runtime = O(n * m), memory = O(n + m), where n = |a|, m = |queries|. Online algorithm.
/* template <typename T>
std::vector<T> maximumRangeSumQueryDirect(const std::vector<T>& a,
                                          const std::vector<std::pair<size_t, size_t>>& queries)
{
  return a;
} */
#endif  // APPLICATIONS_DATA_STRUCTURES_CLOSEST_IN_RANGE_QUERY_INCLUDED
