#ifndef APPLICATIONS_DATA_STRUCTURES_RANGE_MINIMUM_QUERY_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_RANGE_MINIMUM_QUERY_INCLUDED

#include <algorithm>
#include <stack>
#include <vector>

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union.h"

template <typename T>
std::vector<T> rangeMinimumQueryNaive(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [l, r] : queries) {
    if (r < l) {
      throw std::overflow_error("invalid query: r < l");
    }
    if (n <= r) {
      throw std::overflow_error("invalid query: n <= r");
    }
    T min = a[l];
    for (size_t i = l + 1; i <= r; ++i) {
      min = std::min(a[i], min);
    }
    ret.push_back(min);
  }
  return ret;
}

// runtime = O(m * alpha(n) + n), memory = O(m + n), where n = |a|, m = |queries|.
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
    if (r < l) {
      throw std::overflow_error("invalid query: r < l");
    }
    if (n <= r) {
      throw std::overflow_error("invalid query: n <= r");
    }
    Query q = {l, r, idx};
    container[r].push_back(std::move(q));
  }
  std::stack<size_t> s;
  DisjointSetUnion d(n);
  for (size_t i = 0; i < n; i++) {
    while (!s.empty() && a[s.top()] > a[i]) {
      auto& parent = d.getParentMutable();
      parent[s.top()] = i;
      s.pop();
    }
    s.push(i);
    for (const Query& q : container[i]) {
      ret[q.idx] = a[d.findSet(q.l)];
    }
  }
  return ret;
}
#endif  // APPLICATIONS_DATA_STRUCTURES_RANGE_MINIMUM_QUERY_INCLUDED
