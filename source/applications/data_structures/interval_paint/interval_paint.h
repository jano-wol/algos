#ifndef APPLICATIONS_DATA_STRUCTURES_INTERVAL_PAINT_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_INTERVAL_PAINT_INCLUDED

#include <algorithm>
#include <iostream>
#include <vector>

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union_extra.h"

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

// runtime = O((m + n) * alpha(n)), memory = O(m + n), n = |base_interval|, m = |query|.
std::vector<size_t> intervalPaintDisjointSetUnionExtra(
    size_t n, const std::vector<std::pair<std::pair<size_t, size_t>, size_t>>& queries)
{
  std::vector<size_t> ret(n);
  if (queries.size() == 0) {
    return ret;
  }
  std::vector<size_t> extra_;
  for (size_t i = 0; i < n + 1; ++i) {
    extra_.push_back(i);
  }
  auto extraOp = [](size_t a, size_t b, std::vector<size_t>& extra) -> void {
    extra[a] = std::max(extra[a], extra[b]);
  };
  DisjointSetUnionExtra<size_t> d(n + 1, std::move(extra_), std::move(extraOp));

  for (int i = queries.size() - 1; i >= 0; i--) {
    const auto& [l, r] = queries[i].first;
    if (r < l) {
      throw std::overflow_error("invalid query: r < l");
    }
    if (n <= r) {
      throw std::overflow_error("invalid query: n <= r");
    }
    size_t c = queries[i].second;

    size_t curr = l;
    while (true) {
      curr = d.findSet(curr);
      size_t next = d.getExtra()[curr];
      next = d.findSet(next);
      if (next == curr) {
        ret[next] = c;
        auto& extraMutable = d.getExtraMutable();
        extraMutable[next] = extraMutable[next + 1];
        if (next + 1 <= r) {
          curr = next + 1;
        } else {
          break;
        }
      } else {
        size_t next2 = d.getExtra()[next];
        next2 = d.findSet(next2);
        if (next != next2) {
          d.unionSets(curr, next);
        }
        if (next <= r) {
          curr = next;
        } else {
          break;
        }
      }
    }
  }
  return ret;
}

#endif  // APPLICATIONS_DATA_STRUCTURES_INTERVAL_PAINT_INCLUDED
