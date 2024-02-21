#ifndef ALGOS_GRAPHS_KRUSKAL_INCLUDED
#define ALGOS_GRAPHS_KRUSKAL_INCLUDED

#include <algorithm>
#include <iostream>
#include <vector>

#include "./../../data_structures/disjoint_set_union/disjoint_set_union.h"

template <typename T>
class Kruskal
{
public:
  struct Edge
  {
    size_t u;
    size_t v;
    T weight;
    bool operator<(Edge const& other) { return weight < other.weight; }
  };

  // runtime = O(m log(m) + n), memory = O(m + n), where n = |V|, m = |E|.
  static std::vector<size_t> kruskal(size_t n, std::vector<Edge> edges)
  {
    std::vector<std::pair<Edge, size_t>> extendedEdges;
    extendedEdges.reserve(edges.size());
    std::vector<std::pair<Edge, size_t>> spanningTree;
    spanningTree.reserve(n);

    size_t idx = 0;
    for (const auto& edge : edges) {
      extendedEdges.push_back({edge, idx});
    }
    std::sort(extendedEdges.begin(), extendedEdges.end(),
              [](auto& left, auto& right) { return left.first < right.first; });
    DisjointSetUnion d(n);

    for (const auto& e : extendedEdges) {
      if (d.findSet(e.first.u) != d.findSet(e.first.v)) {
        spanningTree.push_back(e);
        d.unionSets(e.first.u, e.first.v);
      }
    }
    std::vector<size_t> ret;
    ret.reserve(n);
    for (const auto& edge : spanningTree) {
      ret.push_back(edge.second);
    }
    return ret;
  }
};

#endif  // ALGOS_GRAPHS_KRUSKAL_INCLUDED
