#ifndef ALGOS_GRAPHS_BFS_INCLUDED
#define ALGOS_GRAPHS_BFS_INCLUDED

#include <algorithm>
#include <iostream>
#include <optional>
#include <queue>
#include <vector>

class Bfs
{
public:
  // element vector, visited, distance from source, parent.
  using ComponentStructure =
      std::pair<std::pair<std::vector<size_t>, std::vector<bool>>, std::pair<std::vector<int>, std::vector<int>>>;

  // runtime = O(m), memory = O(m)
  Bfs(size_t n_, std::vector<std::vector<size_t>> adj_) : n(n_), adj(std::move(adj_)) {}

  // runtime = O(m + n), memory = O(m + n)
  std::vector<size_t> partitiate()
  {
    std::vector<size_t> ret(n);
    std::vector<bool> visited(n);
    size_t partitionIdx = 0;
    for (size_t i = 0; i < n; ++i) {
      if (!visited[i]) {
        bfsLight(i, partitionIdx, ret, visited);
        ++partitionIdx;
      }
    }
    return ret;
  }

  // runtime = O(m + n), memory = O(m + n)
  ComponentStructure getComponent(size_t source)
  {
    std::vector<size_t> component;
    std::queue<size_t> q;
    std::vector<bool> visited(n);
    std::vector<int> distance(n, -1);
    std::vector<int> parent(n, -1);
    q.push(source);
    visited[source] = true;
    distance[source] = 0;
    component.push_back(source);
    while (!q.empty()) {
      size_t v = q.front();
      q.pop();
      for (size_t u : adj[v]) {
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

  // runtime = O(1), memory = O(1)
  std::optional<size_t> getDistanceFromSource(size_t target, const ComponentStructure& structure)
  {
    if (!structure.first.second[target]) {
      std::nullopt;
    }
    return structure.second.first[target];
  }

  // runtime = O(n), memory = O(n)
  std::optional<std::vector<size_t>> getPathFromSource(size_t target, const ComponentStructure& structure)
  {
    if (!structure.first.second[target]) {
      std::nullopt;
    }
    std::vector<size_t> ret;
    for (int v = target; v != -1; v = structure.second.second[v]) {
      ret.push_back(v);
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
  }

private:
  size_t n;
  std::vector<std::vector<size_t>> adj;

  void bfsLight(size_t source, size_t partitionIdx, std::vector<size_t>& ret, std::vector<bool>& visited)
  {
    std::queue<size_t> q;
    q.push(source);
    visited[source] = true;
    ret[source] = partitionIdx;
    while (!q.empty()) {
      size_t v = q.front();
      q.pop();
      for (size_t u : adj[v]) {
        if (!visited[u]) {
          visited[u] = true;
          ret[u] = partitionIdx;
        }
      }
    }
  }
};

#endif  // ALGOS_GRAPHS_BFS_INCLUDED