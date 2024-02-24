#ifndef ALGOS_DATA_STRUCTURES_GRAPH_INCLUDED
#define ALGOS_DATA_STRUCTURES_GRAPH_INCLUDED

#include <iostream>
#include <optional>
#include <vector>

class Graph
{
public:
  Graph(size_t n_, std::vector<std::pair<size_t, size_t>> edges_) : n(n_), edges(std::move(edges_)) {}
  Graph(std::vector<std::vector<size_t>> adj_) : n(adj_.size()), adj(std::move(adj_)) {}
  
  size_t getN() const { return n; }
  const std::vector<std::pair<size_t, size_t>>& getEdges()
  {
    if (edges) {
      return *edges;
    }
    std::vector<std::pair<size_t, size_t>> edges_;
    for (size_t idx = 0; idx < adj->size(); ++idx) {
      const auto& v = adj->at(idx);
      for (auto idx2 : v) {
        if (idx <= idx2) {
          edges_.push_back({idx, idx2});
        }
      }
    }
    edges = std::move(edges_);
    return *edges;
  }

  const std::vector<std::vector<size_t>>& getAdj()
  {
    if (adj) {
      return *adj;
    }
    std::vector<std::vector<size_t>> adj_(n);
    for (const auto& [x, y] : *edges) {
      if (x != y) {
        adj_[x].push_back(y);
        adj_[y].push_back(x);
      } else {
        adj_[x].push_back(x);
      }
    }
    adj = std::move(adj_);
    return *adj;
  }

private:
  size_t n;
  std::optional<std::vector<std::pair<size_t, size_t>>> edges;
  std::optional<std::vector<std::vector<size_t>>> adj;
};

#endif  // ALGOS_DATA_STRUCTURES_GRAPH_INCLUDED
