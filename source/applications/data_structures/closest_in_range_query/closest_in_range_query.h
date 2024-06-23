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
T absImpl(T a, T b)
{
  return ((a - b) > 0) ? (a - b) : (b - a);
}

template <typename T>
T getClosestInRangeNaive(const std::vector<T>& a, T val)
{
  T ret = a[0];
  T minDiff = absImpl(a[0], val);
  for (size_t i = 1; i < a.size(); ++i) {
    T diff = absImpl(a[i], val);
    if (diff < minDiff) {
      minDiff = diff;
      ret = a[i];
    }
  }
  return ret;
}

template <typename T>
void queryImpl(size_t v, size_t currL, size_t currR, size_t l, size_t r, T val, std::pair<T, T>& result,
               const SortedTree<T>& sot)
{
  const auto& t = sot.getT();
  if (currL > currR || currL > r || l > currR) {
    return;
  }
  if (l <= currL && currR <= r) {
    auto it1 = std::lower_bound(t[v].answer.begin() + l, t[v].answer.begin() + r + 1, val);
    auto it2 = std::upper_bound(t[v].answer.begin() + l, t[v].answer.begin() + r + 1, val);
    T x = *it1;
    if (absImpl(val, x) < result.second) {
      result.second = absImpl(val, x);
      result.first = x;
    }
    T y = *it2;
    if (absImpl(val, y) < result.second) {
      result.second = absImpl(val, y);
      result.first = y;
    }
    return;
  }
  size_t tm = (currL + currR) / 2;
  queryImpl(v * 2, currL, tm, l, r, val, result, sot);
  queryImpl(v * 2 + 1, tm + 1, currR, l, r, val, result, sot);
}

template <typename T>
T getClosestInRange(size_t l, size_t r, T val, const std::vector<T>& a, const SortedTree<T>& sot)
{
  std::pair<T, T> result(a[0], absImpl(a[0], val));
  queryImpl(1, 0, a.size() - 1, l, r, val, result, sot);
  const auto& [ret, diff] = result;
  return ret;
}
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

// runtime = O(n * log(n) + m * log(n) * log(n)), memory = O(n * log(n) + m), where n = |a|, m = |queries|. Online
// algorithm.
template <typename T>
std::vector<T> closestInRangeQuerySortedTree(const std::vector<T>& a,
                                             const std::vector<std::pair<std::pair<size_t, size_t>, T>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  SortedTree<T> sot(a);
  for (const auto& [bounds, val] : queries) {
    const auto& [l, r] = bounds;
    checkClosestInRangeQuery(l, r, n);
    ret.push_back(getClosestInRange(l, r, val, a, sot));
  }
  return ret;
}
#endif  // APPLICATIONS_DATA_STRUCTURES_CLOSEST_IN_RANGE_QUERY_INCLUDED
