#ifndef APPLICATIONS_GRAPHS_NUMBER_OF_COMPONENTS_INCLUDED
#define APPLICATIONS_GRAPHS_NUMBER_OF_COMPONENTS_INCLUDED

#include <set>

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union.h"
#include "./../../../algos/data_structures/graph/graph.h"
#include "./../../../algos/graphs/bfs/bfs.h"

size_t numberOfComponentsNaive(Graph& g)
{
  size_t ret = 0;
  size_t n = g.getN();
  const auto& adj = g.getAdj();
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

// runtime = O(m + n), memory = O(m + n), where n = |V|, m = |E|.
size_t numberOfComponentsBFS(Graph& g)
{
  BFS bfs(g);
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

// runtime = O(n + m * alpha(n)), memory = O(m + n). Online algorithm.
size_t numberOfComponentsDisjointSetUnion(Graph& g)
{
  DisjointSetUnion d(g.getN());
  const auto& edges = g.getEdges();
  for (const auto& [a, b] : edges) {
    d.unionSets(a, b);
  }
  return d.getNumberOfComponents();
}

#endif  // APPLICATIONS_GRAPHS_NUMBER_OF_COMPONENTS_INCLUDED
