#ifndef APPLICATIONS_GRAPHS_NUMBER_OF_COMPONENTS_INCLUDED
#define APPLICATIONS_GRAPHS_NUMBER_OF_COMPONENTS_INCLUDED

#include <set>

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union.h"
#include "./../../../algos/graphs/bfs/bfs.h"

namespace
{
std::vector<std::vector<size_t>> edgesToAdj(size_t n, std::vector<std::pair<size_t, size_t>> edges)
{
  std::vector<std::vector<size_t>> adj(n);
  for (const auto& [x, y] : edges) {
    if (x != y) {
      adj[x].push_back(y);
      adj[y].push_back(x);
    } else {
      adj[x].push_back(x);
    }
  }
  return adj;
}
}  // namespace

size_t numberOfComponentsNaive(size_t n, std::vector<std::vector<size_t>> adj)
{
  size_t ret = 0;
  std::vector<bool> visited(n, false);
  for (size_t i = 0; i < n; ++i) {
    if (visited[i] == true) {
      continue;
    }
    ++ret;
    std::set<size_t> curr;
    curr.insert(i);
    while (!curr.empty()) {
      std::set<size_t> next;
      for (auto c : curr) {
        visited[c] = true;
        for (auto x : adj[c]) {
          if ((visited[x] == false) && (curr.count(x) == 0)) {
            next.insert(x);
          }
        }
      }
      curr = next;
    }
  }
  return ret;
}

size_t numberOfComponentsNaive(size_t n, std::vector<std::pair<size_t, size_t>> edges)
{
  auto adj = edgesToAdj(n, edges);
  size_t ret = numberOfComponentsNaive(n, adj);
  return ret;
}

// runtime = O(m + n), memory = O(m + n), where n = |V|, m = |E|.
size_t numberOfComponentsBFS(size_t n, std::vector<std::vector<size_t>> adj)
{
  BFS bfs(n, std::move(adj));
  auto components = bfs.partitiate();
  int ret = -1;
  for (auto c : components) {
    if (int(c) > ret) {
      ret = c;
    }
  }
  ++ret;
  return ret;
}

// runtime = O(m + n), memory = O(m + n), where n = |V|, m = |E|.
size_t numberOfComponentsBFS(size_t n, std::vector<std::pair<size_t, size_t>> edges)
{
  auto adj = edgesToAdj(n, edges);
  size_t ret = numberOfComponentsBFS(n, adj);
  return ret;
}

// runtime = O(m * alpha(n) + n), memory = O(m + n). Online algorithm.
size_t numberOfComponentsDisjointSetUnion(size_t n, std::vector<std::vector<size_t>> adj)
{
  DisjointSetUnion d(n);
  for (size_t i = 0; i < n; ++i) {
    for (auto j : adj[i]) {
      d.unionSets(i, j);
    }
  }
  return d.getNumberOfComponents();
}

// runtime = O(m * alpha(n) + n), memory = O(m + n). Online algorithm.
size_t numberOfComponentsDisjointSetUnion(size_t n, std::vector<std::pair<size_t, size_t>> edges)
{
  DisjointSetUnion d(n);
  for (const auto& [a, b] : edges) {
    d.unionSets(a, b);
  }
  return d.getNumberOfComponents();
}

#endif  // APPLICATIONS_GRAPHS_NUMBER_OF_COMPONENTS_INCLUDED
