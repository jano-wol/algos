#ifndef APPLICATIONS_DATA_STRUCTURES_MAXIMUM_RANGE_SUM_QUERY_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_MAXIMUM_RANGE_SUM_QUERY_INCLUDED

#include <algorithm>
#include <iostream>
#include <vector>

#include "./../../../algos/data_structures/segment_tree/segment_tree.h"

namespace algos::maximum_range_sum_query_utils
{
void checkMaximumRangeSumQuery(size_t l, size_t r, size_t n)
{
  if (r < l) {
    throw std::out_of_range("invalid query: r < l");
  }
  if (n <= r) {
    throw std::out_of_range("invalid query: n <= r");
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

template <typename T>
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
}
}  // namespace algos::maximum_range_sum_query_utils

template <typename T>
std::vector<T> maximumRangeSumQueryNaive(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [l, r] : queries) {
    algos::maximum_range_sum_query_utils::checkMaximumRangeSumQuery(l, r, n);
    std::vector<T> currVec(a.begin() + l, a.begin() + r + 1);
    ret.push_back(algos::maximum_range_sum_query_utils::getMaximumRangeSumNaive(currVec));
  }
  return ret;
}

// runtime = O(n * m), memory = O(n + m), where n = |a|, m = |queries|. Online algorithm.
template <typename T>
std::vector<T> maximumRangeSumQueryDirect(const std::vector<T>& a,
                                          const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [l, r] : queries) {
    algos::maximum_range_sum_query_utils::checkMaximumRangeSumQuery(l, r, n);
    std::vector<T> currVec(a.begin() + l, a.begin() + r + 1);
    ret.push_back(algos::maximum_range_sum_query_utils::getMaximumRangeSumDirect(currVec));
  }
  return ret;
}

// runtime = O(n + m * log(n)), memory = O(n + m), where n = |a|, m = |queries|. Online algorithm. Vector a can be
// mutated by SegmentTree::modify typically in O(log(n)) runtime. (The precise mutate runtime is stated at modify.)
template <typename T>
std::vector<T> maximumRangeSumQuerySegmentTree(const std::vector<T>& a,
                                               const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  struct Q
  {
    T sum;
    T leftMax;
    T rightMax;
    T ans;
  };
  std::function<Q(T)> canonicAnswer = [](T v) -> Q {
    T val = ((0 <= v) ? v : 0);
    return {v, val, val, val};
  };
  std::function<Q(const Q&, const Q&)> compositeAnswers = [](const Q& a1, const Q& a2) -> Q {
    T sum = a1.sum + a2.sum;
    T leftMax = std::max(a1.leftMax, a1.sum + a2.leftMax);
    T rightMax = std::max(a2.rightMax, a2.sum + a1.rightMax);
    T ans = std::max(std::max(a1.ans, a2.ans), a1.rightMax + a2.leftMax);
    return {sum, leftMax, rightMax, ans};
  };
  SegmentTree<T, Q> s(a, std::move(canonicAnswer), std::move(compositeAnswers), {0, 0, 0, 0});
  for (const auto& [l, r] : queries) {
    algos::maximum_range_sum_query_utils::checkMaximumRangeSumQuery(l, r, n);
    ret.push_back(s.query(l, r).ans);
  }
  return ret;
}
#endif  // APPLICATIONS_DATA_STRUCTURES_MAXIMUM_RANGE_SUM_QUERY_INCLUDED
