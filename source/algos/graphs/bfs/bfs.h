#ifndef ALGOS_GRAPHS_BFS_INCLUDED
#define ALGOS_GRAPHS_BFS_INCLUDED

#include <algorithm>
#include <iostream>
#include <optional>
#include <queue>
#include <vector>

#include "./../../../algos/data_structures/graph/graph.h"

class BFS
{
public:
  // element vector, visited, distance from source, parent.
  using ComponentStructure =
      std::pair<std::pair<std::vector<size_t>, std::vector<bool>>, std::pair<std::vector<int>, std::vector<int>>>;

  // runtime = O(m), memory = O(m)
  BFS(Graph g_) : g(std::move(g_)) {}

  // runtime = O(m + n), memory = O(m + n), where n = |V|, m = |E|.
  std::vector<size_t> partitiate()
  {
    std::vector<size_t> ret(g.getN());
    std::vector<bool> visited(g.getN());
    size_t partitionIdx = 0;
    for (size_t i = 0; i < g.getN(); ++i) {
      if (!visited[i]) {
        bfsPartitiate(i, partitionIdx, ret, visited);
        ++partitionIdx;
      }
    }
    return ret;
  }

  // runtime = O(m + n), memory = O(m + n), where n = |V|, m = |E|.
  ComponentStructure getComponent(size_t source)
  {
    if (source >= g.getN()) {
      throw std::overflow_error("source is out of bound");
    }
    std::vector<size_t> component;
    std::queue<size_t> q;
    std::vector<bool> visited(g.getN());
    std::vector<int> distance(g.getN(), -1);
    std::vector<int> parent(g.getN(), -1);
    q.push(source);
    visited[source] = true;
    distance[source] = 0;
    component.push_back(source);
    while (!q.empty()) {
      size_t v = q.front();
      q.pop();
      for (size_t u : g.getAdj().at(v)) {
        if (!visited[u]) {
          visited[u] = true;
          component.push_back(u);
          q.push(u);
          distance[u] = distance[v] + 1;
          parent[u] = v;
        }
      }
    }
    return {{std::move(component), std::move(visited)}, {std::move(distance), std::move(parent)}};
  }

  // runtime = O(1), memory = O(1).
  std::optional<size_t> getDistanceFromSource(size_t target, const ComponentStructure& structure)
  {
    if (target >= g.getN()) {
      throw std::overflow_error("target is out of bound");
    }
    if (!structure.first.second[target]) {
      return std::nullopt;
    }
    return structure.second.first[target];
  }

  // runtime = O(n), memory = O(n).
  std::optional<std::vector<size_t>> getPathFromSource(size_t target, const ComponentStructure& structure)
  {
    if (target >= g.getN()) {
      throw std::overflow_error("target is out of bound");
    }
    if (!structure.first.second[target]) {
      return std::nullopt;
    }
    std::vector<size_t> ret;
    for (int v = target; v != -1; v = structure.second.second[v]) {
      ret.push_back(v);
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
  }

private:
  Graph g;

  void bfsPartitiate(size_t source, size_t partitionIdx, std::vector<size_t>& ret, std::vector<bool>& visited)
  {
    std::queue<size_t> q;
    q.push(source);
    visited[source] = true;
    ret[source] = partitionIdx;
    while (!q.empty()) {
      size_t v = q.front();
      q.pop();
      for (size_t u : g.getAdj().at(v)) {
        if (!visited[u]) {
          visited[u] = true;
          ret[u] = partitionIdx;
          q.push(u);
        }
      }
    }
  }
};

#endif  // ALGOS_GRAPHS_BFS_INCLUDED
