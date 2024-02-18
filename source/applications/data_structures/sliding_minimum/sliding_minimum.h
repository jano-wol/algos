#ifndef APPLICATIONS_DATA_STRUCTURES_SLIDING_MINIMUM_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_SLIDING_MINIMUM_INCLUDED

#include <algorithm>
#include <vector>

#include "./../../../algos/data_structures/minimum_queue/minimum_queue.h"

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

#endif  // APPLICATIONS_DATA_STRUCTURES_SLIDING_MINIMUM_INCLUDED
