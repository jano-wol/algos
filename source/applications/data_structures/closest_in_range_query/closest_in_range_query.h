#ifndef APPLICATIONS_DATA_STRUCTURES_CLOSEST_IN_RANGE_QUERY_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_CLOSEST_IN_RANGE_QUERY_INCLUDED

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "./../../../algos/data_structures/segment_tree/sorted_tree.h"

namespace algos::closest_in_range_utils
{
void checkClosestInRangeQuery(size_t l, size_t r, size_t n)
{
  if (r < l) {
    throw std::out_of_range("invalid query: r < l");
  }
  if (n <= r) {
    throw std::out_of_range("invalid query: n <= r");
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
  bool over = false;
  if (currL > currR || currL > r || l > currR) {
    return;
  }
  if (l <= currL && currR <= r) {
    auto it = std::lower_bound(t[v].answer.begin(), t[v].answer.end(), val);
    if (it == t[v].answer.end()) {
      --it;
      over = true;
    }
    T x = *it;
    if (absImpl(val, x) < result.second) {
      result.second = absImpl(val, x);
      result.first = x;
    }
    if ((over == false) && (it != (t[v].answer.begin()))) {
      --it;
      x = *it;
      if (absImpl(val, x) < result.second) {
        result.second = absImpl(val, x);
        result.first = x;
      }
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
  std::pair<T, T> result(a[l], absImpl(a[l], val));
  queryImpl(1, 0, a.size() - 1, l, r, val, result, sot);
  const auto& [ret, diff] = result;
  return ret;
}
}  // namespace algos::closest_in_range_utils

template <typename T>
std::vector<T> closestInRangeQueryNaive(const std::vector<T>& a,
                                        const std::vector<std::pair<std::pair<size_t, size_t>, T>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [bounds, val] : queries) {
    const auto& [l, r] = bounds;
    algos::closest_in_range_utils::checkClosestInRangeQuery(l, r, n);
    std::vector<T> currVec(a.begin() + l, a.begin() + r + 1);
    ret.push_back(algos::closest_in_range_utils::getClosestInRangeNaive(currVec, val));
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
    algos::closest_in_range_utils::checkClosestInRangeQuery(l, r, n);
    ret.push_back(algos::closest_in_range_utils::getClosestInRange(l, r, val, a, sot));
  }
  return ret;
}
#endif  // APPLICATIONS_DATA_STRUCTURES_CLOSEST_IN_RANGE_QUERY_INCLUDED
