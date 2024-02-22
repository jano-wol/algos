#ifndef APPLICATIONS_GRAPHS_LEAST_COMMON_ANCESTOR_INCLUDED
#define APPLICATIONS_GRAPHS_LEAST_COMMON_ANCESTOR_INCLUDED

#include <set>

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union.h"
#include "./../../../algos/graphs/bfs/bfs.h"

namespace
{
std::vector<std::vector<size_t>> edgesToAdjDirected(size_t n, std::vector<std::pair<size_t, size_t>> edges)
{
  std::vector<std::vector<size_t>> adj(n);
  for (const auto& [x, y] : edges) {
    adj[x].push_back(y);
  }
  return adj;
}

std::vector<size_t> adjToAncestor(const std::vector<std::vector<size_t>>& adj)
{
  size_t n = adj.size();
  std::vector<size_t> ancestor(n);
  for (size_t idx = 0; idx < n; ++idx) {
    ancestor[idx] = idx;
  }
  for (size_t idx = 0; idx < n; ++idx) {
    for (auto v : adj.at(idx)) {
      ancestor[v] = idx;
    }
  }
  return ancestor;
}

std::vector<size_t> pathToRoot(std::vector<size_t> ancestor, size_t start)
{
  std::vector<size_t> ret;
  while (start != ancestor[start]) {
    ret.push_back(start);
    start = ancestor[start];
  }
  ret.push_back(start);
  return ret;
}
}  // namespace

std::vector<size_t> leastCommonAncestorNaive(const std::vector<size_t>& ancestor,
                                             const std::vector<std::pair<size_t, size_t>>& querys)
{
  std::vector<size_t> ret;
  ret.reserve(querys.size());
  for (const auto& [u, v] : querys) {
    auto p1 = pathToRoot(ancestor, u);
    auto p2 = pathToRoot(ancestor, v);
    size_t r = ancestor.size();
    for (int idx = p2.size() - 1; idx >= 0; --idx) {
      size_t target = p2[idx];
      bool isInP1 = false;
      for (auto w : p1) {
        if (w == target) {
          isInP1 = true;
          break;
        }
      }
      if (isInP1) {
        r = target;
      } else {
        break;
      }
    }
    ret.push_back(r);
  }
  return ret;
}

std::vector<size_t> leastCommonAncestorNaive(const std::vector<std::vector<size_t>>& adj,
                                             const std::vector<std::pair<size_t, size_t>>& querys)

{
  auto ancestor = adjToAncestor(adj);
  return leastCommonAncestorNaive(ancestor, querys);
}

std::vector<size_t> leastCommonAncestorNaive(size_t n, const std::vector<std::pair<size_t, size_t>>& edgesDirected,
                                             const std::vector<std::pair<size_t, size_t>>& querys)
{
  auto adj = edgesToAdjDirected(n, edgesDirected);
  return leastCommonAncestorNaive(adj, querys);
}

#endif  // APPLICATIONS_GRAPHS_LEAST_COMMON_ANCESTOR_INCLUDED
