#ifndef APPLICATIONS_DATA_STRUCTURES_RANGE_SUM_QUERY_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_RANGE_SUM_QUERY_INCLUDED

#include <algorithm>
#include <stack>
#include <vector>

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union_compress.h"
#include "./../../../algos/data_structures/sparse_table/sparse_table_min.h"

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

#endif  // APPLICATIONS_DATA_STRUCTURES_RANGE_SUM_QUERY_INCLUDED
