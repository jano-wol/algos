#ifndef APPLICATIONS_DATA_STRUCTURES_RANGE_MINIMUM_QUERY_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_RANGE_MINIMUM_QUERY_INCLUDED

#include <algorithm>
#include <vector>

#include "./../../../algos/data_structures/minimum_queue/minimum_queue.h"
#include "./../../../algos/data_structures/sparse_table/sparse_table_min.h"

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
#endif  // APPLICATIONS_DATA_STRUCTURES_RANGE_MINIMUM_QUERY_INCLUDED
