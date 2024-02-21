#ifndef APPLICATIONS_DATA_STRUCTURES_INTERVAL_PAINT_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_INTERVAL_PAINT_INCLUDED

#include <algorithm>
#include <iostream>
#include <vector>

#include "./../../../algos/data_structures/minimum_queue/minimum_queue.h"
#include "./../../../algos/data_structures/sparse_table/sparse_table_min.h"

std::vector<size_t> intervalPaintNaive(size_t n,
                                       const std::vector<std::pair<std::pair<size_t, size_t>, size_t>>& queries)
{
  std::vector<size_t> ret(n);
  for (const auto& [interval, c] : queries) {
    const auto& [l, r] = interval;
    if (r < l) {
      throw std::overflow_error("invalid query: r < l");
    }
    if (n <= r) {
      throw std::overflow_error("invalid query: n <= r");
    }
    for (size_t i = l; i <= r; ++i) {
      ret[i] = c;
    }
  }
  return ret;
}
#endif  // APPLICATIONS_DATA_STRUCTURES_INTERVAL_PAINT_INCLUDED
