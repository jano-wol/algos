#ifndef ALGOS_DATA_STRUCTURES_MO_INCLUDED
#define ALGOS_DATA_STRUCTURES_MO_INCLUDED

#include <iostream>
#include <memory>
#include <optional>
#include <vector>

#include "i_mo_object.h"

template <typename R>
class Mo
{
public:
  Mo(std::unique_ptr<IMoObject<R>> iMoObjectPtr_) : iMoObjectPtr(std::move(iMoObjectPtr_)) {}

  // runtime = O(n * sqrt(m) * F), memory = O(n + m), where n = |mo object base|, m = |queries|, and F is
  // the worst runtime of add, remove, solve virtuals.
  std::vector<R> solve(const std::vector<std::pair<size_t, size_t>>& queries, size_t blockSize = 0)
  {
    if (blockSize == 0) {
      size_t n = iMoObjectPtr->getN();
      blockSize = n / (size_t(sqrt(queries.size() + .0)) + 1);
    }
    std::vector<MoQuery> moQueries;
    moQueries.reserve(queries.size());
    for (size_t idx = 0; idx < queries.size(); ++idx) {
      moQueries.push_back({queries[idx].first, queries[idx].second, idx, queries[idx].first / blockSize});
    }
    std::sort(moQueries.begin(), moQueries.end());
    std::vector<R> ret(queries.size());
    int cur_l = 0;
    int cur_r = -1;
    for (const auto& q : moQueries) {
      while (cur_l > int(q.l)) {
        cur_l--;
        iMoObjectPtr->add(cur_l);
      }
      while (cur_r < int(q.r)) {
        cur_r++;
        iMoObjectPtr->add(cur_r);
      }
      while (cur_l < int(q.l)) {
        iMoObjectPtr->remove(cur_l);
        cur_l++;
      }
      while (cur_r > int(q.r)) {
        iMoObjectPtr->remove(cur_r);
        cur_r--;
      }
      ret[q.idx] = iMoObjectPtr->solve();
    }
    return ret;
  }

  const std::unique_ptr<IMoObject<R>>& getMoObjectPtr() { return iMoObjectPtr; };

private:
  std::unique_ptr<IMoObject<R>> iMoObjectPtr;

  struct MoQuery
  {
    size_t l;
    size_t r;
    size_t idx;
    size_t orderVal;
    bool operator<(const MoQuery& other) const
    {
      if (orderVal != other.orderVal) {
        return orderVal < other.orderVal;
      }
      return (orderVal & 1) ? (r < other.r) : (r > other.r);
    };
  };
};

#endif  // ALGOS_DATA_STRUCTURES_MO_INCLUDED
