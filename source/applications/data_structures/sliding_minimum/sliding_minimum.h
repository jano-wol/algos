#ifndef APPLICATIONS_DATA_STRUCTURES_SLIDING_MINIMUM_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_SLIDING_MINIMUM_INCLUDED

#include <algorithm>
#include <limits>
#include <vector>

#include "./../../../algos/data_structures/minimum_queue/minimum_queue.h"
#include "./../../../algos/data_structures/segment_tree/segment_tree.h"
#include "./../../../algos/data_structures/sparse_table/sparse_table_min.h"
#include "./../../../algos/data_structures/sqrt_tree/sqrt_tree.h"

template <typename T>
std::vector<T> slidingMinimumNaive(const std::vector<T>& v, size_t w)
{
  if (w == 0 || v.size() < w) {
    return {};
  }
  std::vector<T> ret;
  for (size_t i = 0; i + w <= v.size(); ++i) {
    T currMin = v[i];
    for (size_t j = 1; j < w; ++j) {
      currMin = std::min(currMin, v[i + j]);
    }
    ret.push_back(currMin);
  }
  return ret;
}

// runtime = O(n), memory = O(n), where n = |v|.
template <typename T>
std::vector<T> slidingMinimumMinimumQueue(const std::vector<T>& v, size_t w)
{
  if (w == 0 || v.size() < w) {
    return {};
  }
  std::vector<T> ret;
  MinimumQueue<T> q;
  for (size_t i = 0; i < w; ++i) {
    q.push(v[i]);
  }
  ret.push_back(q.getMinimum());
  for (size_t i = w; i < v.size(); ++i) {
    q.pop();
    q.push(v[i]);
    ret.push_back(q.getMinimum());
  }
  return ret;
}

// runtime = O(n * log(n)), memory = O(n * log(n)), where n = |v|.
template <typename T>
std::vector<T> slidingMinimumSparseTableMin(const std::vector<T>& v, size_t w)
{
  if (w == 0 || v.size() < w) {
    return {};
  }
  std::vector<T> ret;
  SparseTableMin<T> t(v);
  for (size_t i = 0; i + w <= v.size(); ++i) {
    ret.push_back(t.query(i, i + w - 1));
  }
  return ret;
}

// runtime = O(n * log(n)), memory = O(n), where n = |v|.
template <typename T>
std::vector<T> slidingMinimumSegmentTree(const std::vector<T>& v, size_t w)
{
  if (w == 0 || v.size() < w) {
    return {};
  }
  std::vector<T> ret;
  std::function<T(T)> canonicAnswer = [](T v_) { return v_; };
  std::function<T(T, T)> compositeAnswers = [](T a1, T a2) { return std::min(a1, a2); };
  SegmentTree<T, T> s(v, std::move(canonicAnswer), std::move(compositeAnswers), std::numeric_limits<T>::max());
  for (size_t i = 0; i + w <= v.size(); ++i) {
    ret.push_back(s.query(i, i + w - 1));
  }
  return ret;
}

// runtime = O(n * log(log(n))), memory = O(n), where n = |v|.
template <typename T>
std::vector<T> slidingMinimumSqrtTree(const std::vector<T>& v, size_t w)
{
  if (w == 0 || v.size() < w) {
    return {};
  }
  std::vector<T> ret;
  std::function<T(T, T)> op = [](T a1, T a2) { return std::min(a1, a2); };
  SqrtTree<T> s(v, std::move(op));
  for (size_t i = 0; i + w <= v.size(); ++i) {
    ret.push_back(s.query(i, i + w - 1));
  }
  return ret;
}

#endif  // APPLICATIONS_DATA_STRUCTURES_SLIDING_MINIMUM_INCLUDED
