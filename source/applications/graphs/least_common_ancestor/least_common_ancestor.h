#ifndef APPLICATIONS_GRAPHS_LEAST_COMMON_ANCESTOR_INCLUDED
#define APPLICATIONS_GRAPHS_LEAST_COMMON_ANCESTOR_INCLUDED

#include <set>

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union.h"
#include "./../../../algos/graphs/bfs/bfs.h"

namespace
{
std::vector<std::vector<size_t>> edgesToAdjDirected(size_t n, const std::vector<std::pair<size_t, size_t>>& edges)
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

std::vector<size_t> pathToRoot(const std::vector<size_t>& ancestor, size_t start)
{
  std::vector<size_t> ret;
  while (start != ancestor[start]) {
    ret.push_back(start);
    start = ancestor[start];
  }
  ret.push_back(start);
  return ret;
}

size_t getRoot(const std::vector<size_t>& ancestor)
{
  size_t n = ancestor.size();
  size_t root = n;
  for (size_t idx = 0; idx < n; ++idx) {
    if (idx == ancestor[idx]) {
      root = idx;
      break;
    }
  }
  return root;
}

void dfsDisjointSetUnion(size_t v, const std::vector<std::vector<size_t>>& adj, std::vector<size_t>& a,
                         DisjointSetUnion& d, std::vector<bool>& visited,
                         const std::vector<std::vector<std::pair<size_t, size_t>>>& queries, std::vector<size_t>& ret)
{
  visited[v] = true;
  a[v] = v;
  for (int u : adj[v]) {
    if (!visited[u]) {
      dfsDisjointSetUnion(u, adj, a, d, visited, queries, ret);
      d.unionSets(v, u);
      a[d.findSet(v)] = v;
    }
  }
  for (const auto& [u, idx] : queries[v]) {
    if (visited[u]) {
      ret[idx] = a[d.findSet(u)];
    }
  }
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

std::vector<size_t> leastCommonAncestorNaive(size_t n, const std::vector<std::pair<size_t, size_t>>& downEdges,
                                             const std::vector<std::pair<size_t, size_t>>& querys)
{
  auto adj = edgesToAdjDirected(n, downEdges);
  return leastCommonAncestorNaive(adj, querys);
}

std::vector<size_t> leastCommonAncestorDisjointSetUnion(const std::vector<size_t>& ancestor,
                                                        const std::vector<std::vector<size_t>>& adj,
                                                        const std::vector<std::pair<size_t, size_t>>& querys)
{
  if (querys.empty()) {
    return {};
  }
  std::vector<std::vector<std::pair<size_t, size_t>>> queriesExt(adj.size());
  for (size_t idx = 0; idx < querys.size(); ++idx) {
    const auto& [u, v] = querys[idx];
    queriesExt[u].push_back({v, idx});
    queriesExt[v].push_back({u, idx});
  }
  size_t root = getRoot(ancestor);
  DisjointSetUnion d(adj.size());
  std::vector<size_t> ret(querys.size());
  std::vector<size_t> a(adj.size());
  std::vector<bool> visited(adj.size(), false);
  dfsDisjointSetUnion(root, adj, a, d, visited, queriesExt, ret);
  return ret;
}

std::vector<size_t> leastCommonAncestorDisjointSetUnion(const std::vector<std::vector<size_t>>& adj,
                                                        const std::vector<std::pair<size_t, size_t>>& querys)

{
  auto ancestor = adjToAncestor(adj);
  return leastCommonAncestorDisjointSetUnion(ancestor, adj, querys);
}

std::vector<size_t> leastCommonAncestorDisjointSetUnion(size_t n,
                                                        const std::vector<std::pair<size_t, size_t>>& downEdges,
                                                        const std::vector<std::pair<size_t, size_t>>& querys)
{
  auto adj = edgesToAdjDirected(n, downEdges);
  return leastCommonAncestorDisjointSetUnion(adj, querys);
}

#endif  // APPLICATIONS_GRAPHS_LEAST_COMMON_ANCESTOR_INCLUDED
