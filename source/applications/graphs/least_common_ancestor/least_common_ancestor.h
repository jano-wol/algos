#ifndef APPLICATIONS_GRAPHS_LEAST_COMMON_ANCESTOR_INCLUDED
#define APPLICATIONS_GRAPHS_LEAST_COMMON_ANCESTOR_INCLUDED

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

std::vector<size_t> adjToParent(const std::vector<std::vector<size_t>>& adj)
{
  size_t n = adj.size();
  std::vector<size_t> parent(n);
  for (size_t idx = 0; idx < n; ++idx) {
    parent[idx] = idx;
  }
  for (size_t idx = 0; idx < n; ++idx) {
    for (auto v : adj.at(idx)) {
      parent[v] = idx;
    }
  }
  return parent;
}

std::vector<size_t> pathToRoot(const std::vector<size_t>& parent, size_t start)
{
  std::vector<size_t> ret;
  while (start != parent[start]) {
    ret.push_back(start);
    start = parent[start];
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

void dfsDisjointSetUnion(size_t v, const std::vector<std::vector<size_t>>& adj, std::vector<size_t>& ancestor,
                         DisjointSetUnion& d, std::vector<bool>& visited,
                         const std::vector<std::vector<std::pair<size_t, size_t>>>& queries, std::vector<size_t>& ret)
{
  visited[v] = true;
  ancestor[v] = v;
  for (size_t u : adj[v]) {
    dfsDisjointSetUnion(u, adj, ancestor, d, visited, queries, ret);
    d.unionSets(v, u);
    ancestor[d.findSet(v)] = v;
  }
  for (const auto& [u, idx] : queries[v]) {
    if (visited[u]) {
      ret[idx] = ancestor[d.findSet(u)];
    }
  }
}

std::vector<size_t> leastCommonAncestorNaiveImpl(const std::vector<size_t>& parent,
                                                 const std::vector<std::pair<size_t, size_t>>& queries)
{
  std::vector<size_t> ret;
  ret.reserve(queries.size());
  for (const auto& [u, v] : queries) {
    auto p1 = pathToRoot(parent, u);
    auto p2 = pathToRoot(parent, v);
    size_t r = parent.size();
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

std::vector<size_t> leastCommonAncestorDisjointSetUnionImpl(const std::vector<size_t>& parent,
                                                            const std::vector<std::vector<size_t>>& adj,
                                                            const std::vector<std::pair<size_t, size_t>>& queries)
{
  if (queries.empty()) {
    return {};
  }
  size_t n = adj.size();
  std::vector<std::vector<std::pair<size_t, size_t>>> queriesExt(n);
  for (size_t idx = 0; idx < queries.size(); ++idx) {
    const auto& [u, v] = queries[idx];
    if (n <= u || n <= v) {
      throw std::overflow_error("invalid query: r < l");
    }
    queriesExt[u].push_back({v, idx});
    queriesExt[v].push_back({u, idx});
  }
  size_t root = getRoot(parent);
  DisjointSetUnion d(n);
  std::vector<size_t> ancestor(n);
  std::vector<bool> visited(n, false);
  std::vector<size_t> ret(queries.size());
  dfsDisjointSetUnion(root, adj, ancestor, d, visited, queriesExt, ret);
  return ret;
}
}  // namespace

std::vector<size_t> leastCommonAncestorNaive(const std::vector<std::vector<size_t>>& adj,
                                             const std::vector<std::pair<size_t, size_t>>& queries)

{
  auto parent = adjToParent(adj);
  return leastCommonAncestorNaiveImpl(parent, queries);
}

std::vector<size_t> leastCommonAncestorNaive(size_t n, const std::vector<std::pair<size_t, size_t>>& downEdges,
                                             const std::vector<std::pair<size_t, size_t>>& queries)
{
  auto adj = edgesToAdjDirected(n, downEdges);
  return leastCommonAncestorNaive(adj, queries);
}

// runtime = O(n + m * alpha(n)), memory = O(m + n), where n = |V| = |adj|, m = |queries|
std::vector<size_t> leastCommonAncestorDisjointSetUnion(const std::vector<std::vector<size_t>>& adj,
                                                        const std::vector<std::pair<size_t, size_t>>& queries)

{
  auto parent = adjToParent(adj);
  return leastCommonAncestorDisjointSetUnionImpl(parent, adj, queries);
}

// runtime = O(n + m * alpha(n)), memory = O(m + n), where n = |V| = |adj|, m = |queries|
std::vector<size_t> leastCommonAncestorDisjointSetUnion(size_t n,
                                                        const std::vector<std::pair<size_t, size_t>>& downEdges,
                                                        const std::vector<std::pair<size_t, size_t>>& queries)
{
  auto adj = edgesToAdjDirected(n, downEdges);
  return leastCommonAncestorDisjointSetUnion(adj, queries);
}

#endif  // APPLICATIONS_GRAPHS_LEAST_COMMON_ANCESTOR_INCLUDED
