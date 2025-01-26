#ifndef ALGOS_DATA_STRUCTURES_LINK_CUT_TREE_NAIVE_INCLUDED
#define ALGOS_DATA_STRUCTURES_LINK_CUT_TREE_NAIVE_INCLUDED

#include <iostream>
#include <unordered_set>
#include <vector>

class LinkCutTreeNaive
{
public:
  LinkCutTreeNaive(int n) : adj(n) {}

  void link(int u, int v)
  {
    if (u == v) {
      throw std::invalid_argument("u == v");
    }
    if (connected(u, v)) {
      throw std::invalid_argument("u and v already connected");
    }
    adj[u].insert(v);
    adj[v].insert(u);
  }

  void cut(int u, int v)
  {
    adj[u].erase(v);
    adj[v].erase(u);
  }

  bool connected(int u, int v)
  {
    std::vector<bool> visited(adj.size(), false);
    visited[u] = true;
    std::unordered_set<int> active;
    active.insert(u);
    int currDist = 1;
    while (!active.empty()) {
      std::unordered_set<int> curr;
      for (auto w : active) {
        for (auto n : adj[w]) {
          if (visited[n] == false) {
            visited[n] = true;
            curr.insert(n);
          }
        }
      }
      active = curr;
    }
    return visited[v];
  }

private:
  std::vector<std::unordered_set<int>> adj;
};

#endif  // ALGOS_DATA_STRUCTURES_LINK_CUT_TREE_NAIVE_INCLUDED
