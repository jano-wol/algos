#ifndef APPLICATIONS_DATA_STRUCTURES_RANGE_MINIMUM_QUERY_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_RANGE_MINIMUM_QUERY_INCLUDED

#include <algorithm>
#include <stack>
#include <vector>

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union_compress.h"
#include "./../../../algos/data_structures/sparse_table/sparse_table_min.h"
#include "./../../../algos/data_structures/sqrt_decomposition/sqrt_decomposition_min.h"

namespace
{
void checkMinimumQuery(size_t l, size_t r, size_t n)
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
std::vector<T> rangeMinimumQueryNaive(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [l, r] : queries) {
    checkMinimumQuery(l, r, n);
    T min = a[l];
    for (size_t i = l + 1; i <= r; ++i) {
      min = std::min(a[i], min);
    }
    ret.push_back(min);
  }
  return ret;
}

// runtime = O(n + m * alpha(n)), memory = O(m + n), where n = |a|, m = |queries|.
// (I am not 100% that runtime is correct. Runtime is O(n + m * log(n))) for sure, anyway this algo has good constants.)
template <typename T>
std::vector<T> rangeMinimumQueryDisjointSetUnion(const std::vector<T>& a,
                                                 const std::vector<std::pair<size_t, size_t>>& queries)
{
  struct Query
  {
    size_t l;
    size_t r;
    size_t idx;
  };
  size_t n = a.size();
  std::vector<std::vector<Query>> container(n);
  std::vector<T> ret(queries.size());
  for (size_t idx = 0; idx < queries.size(); ++idx) {
    const auto& [l, r] = queries[idx];
    checkMinimumQuery(l, r, n);
    Query q = {l, r, idx};
    container[r].push_back(std::move(q));
  }
  std::stack<size_t> s;
  DisjointSetUnionCompress d(n);
  for (size_t i = 0; i < n; i++) {
    while (!s.empty() && a[s.top()] > a[i]) {
      d.connect(s.top(), i);
      s.pop();
    }
    s.push(i);
    for (const Query& q : container[i]) {
      ret[q.idx] = a[d.findSet(q.l)];
    }
  }
  return ret;
}

// runtime = O(n * log(n) + m * 1), memory = O(n * log(n) + m), where n = |a|, m = |queries|. Online algorithm.
template <typename T>
std::vector<T> rangeMinimumQuerySparseTable(const std::vector<T>& a,
                                            const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  SparseTableMin<T> t(a);
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [l, r] : queries) {
    checkMinimumQuery(l, r, n);
    ret.push_back(t.query(l, r));
  }
  return ret;
}

// runtime = O(n + m * sqrt(n)), memory = O(n + m), where n = |a|, m = |queries|. Online algorithm. Vector a is mutable
// in O(sqrt(n)) runtime.
template <typename T>
std::vector<T> rangeMinimumQuerySqrtDecomposition(const std::vector<T>& a,
                                                  const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  SqrtDecompositionMin<T> d(a);
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [l, r] : queries) {
    checkMinimumQuery(l, r, n);
    ret.push_back(d.min(l, r));
  }
  return ret;
}

#endif  // APPLICATIONS_DATA_STRUCTURES_RANGE_MINIMUM_QUERY_INCLUDED
