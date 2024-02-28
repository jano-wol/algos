#ifndef APPLICATIONS_DATA_STRUCTURES_RANGE_SUM_QUERY_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_RANGE_SUM_QUERY_INCLUDED

#include <algorithm>
#include <vector>

#include "./../../../algos/data_structures/fenwick/fenwick.h"
#include "./../../../algos/data_structures/sparse_table/sparse_table_disjoint_sum.h"
#include "./../../../algos/data_structures/sparse_table/sparse_table_sum.h"

namespace
{
void checkSumQuery(size_t l, size_t r, size_t n)
{
  if (r < l) {
    throw std::overflow_error("invalid query: r < l");
  }
  if (n <= r) {
    throw std::overflow_error("invalid query: n <= r");
  }
}
}  // namespace

template <typename T>
std::vector<T> rangeSumQueryNaive(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [l, r] : queries) {
    checkSumQuery(l, r, n);
    T sum = a[l];
    for (size_t i = l + 1; i <= r; ++i) {
      sum += a[i];
    }
    ret.push_back(sum);
  }
  return ret;
}

// runtime = O(n log(n) + m * log(n)), memory = O(n log(n)), where n = |a|, m = |queries|. Online algorithm.
template <typename T>
std::vector<T> rangeSumQuerySparseTable(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  SparseTableSum t(a);
  for (const auto& [l, r] : queries) {
    checkSumQuery(l, r, n);
    T sum = t.query(l, r);
    ret.push_back(sum);
  }
  return ret;
}

// runtime = O(n log(n) + m * 1), memory = O(n log(n)), where n = |a|, m = |queries|. Online algorithm.
template <typename T>
std::vector<T> rangeSumQuerySparseTableDisjointSum(const std::vector<T>& a,
                                                   const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  SparseTableDisjointSum t(a);
  for (const auto& [l, r] : queries) {
    checkSumQuery(l, r, n);
    T sum = t.query(l, r);
    ret.push_back(sum);
  }
  return ret;
}

// runtime = O(n + m * log(n)), memory = O(n + m), where n = |a|, m = |queries|. Online algorithm. Vector a is mutable
// in O(log(n)) runtime.
template <typename T>
std::vector<T> rangeSumQueryFenwick(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  Fenwick<T> t(a);
  for (const auto& [l, r] : queries) {
    checkSumQuery(l, r, n);
    T sum = t.sum(l, r);
    ret.push_back(sum);
  }
  return ret;
}

#endif  // APPLICATIONS_DATA_STRUCTURES_RANGE_SUM_QUERY_INCLUDED
