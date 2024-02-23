#ifndef APPLICATIONS_GRAPHS_BRIDGES_INCLUDED
#define APPLICATIONS_GRAPHS_BRIDGES_INCLUDED

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union.h"
#include "./../number_of_components/number_of_components.h"

namespace
{
void makeRoot(size_t v, std::vector<size_t>& twoConnectedComponentsForest, DisjointSetUnion& twoConnected,
              const std::vector<std::pair<size_t, size_t>>& edges)
{
  v = twoConnected.findSet(v);
  size_t childValue = twoConnectedComponentsForest[v];
  while (childValue != edges.size() + 1) {
    const auto& [p, q] = edges[childValue];
    size_t pPrimal = twoConnected.findSet(p);
    size_t qPrimal = twoConnected.findSet(q);
    size_t childValueTmp;
    size_t primal = pPrimal;
    if (pPrimal == v) {
      primal = qPrimal;
    }
    childValueTmp = twoConnectedComponentsForest[primal];
    twoConnectedComponentsForest[primal] = childValue;
    v = primal;
    childValue = childValueTmp;
  }
}

std::pair<std::vector<size_t>, std::vector<size_t>> lca(size_t u, size_t v,
                                                        std::vector<size_t>& twoConnectedComponentsForest,
                                                        DisjointSetUnion& twoConnected,
                                                        const std::vector<std::pair<size_t, size_t>>& edges,
                                                        size_t lcaIteration, std::vector<size_t> lastVisit)
{
  std::vector<size_t> bridgesToDelete;
  std::vector<size_t> twoConnectedPrimalsToUnion;
  ++lcaIteration;
  while (true) {
    twoConnectedPrimalsToUnion.push_back(u);
    size_t childU = twoConnectedComponentsForest[u];
    if (childU != edges.size() + 1) {
      bridgesToDelete.push_back(childU);
      if (lastVisit[u] == lcaIteration) {
        break;
      }
      lastVisit[u] = lcaIteration;
      const auto& [p, q] = edges[childU];
      size_t pPrimal = twoConnected.findSet(p);
      size_t qPrimal = twoConnected.findSet(q);
      if (u != pPrimal) {
        u = pPrimal;
      } else {
        u = qPrimal;
      }
    }
    twoConnectedPrimalsToUnion.push_back(v);
    size_t childV = twoConnectedComponentsForest[v];
    if (childV != edges.size() + 1) {
      bridgesToDelete.push_back(childV);
      if (lastVisit[v] == lcaIteration) {
        break;
      }
      lastVisit[v] = lcaIteration;
      const auto& [p, q] = edges[childV];
      size_t pPrimal = twoConnected.findSet(p);
      size_t qPrimal = twoConnected.findSet(q);
      if (v != pPrimal) {
        v = pPrimal;
      } else {
        v = qPrimal;
      }
    }
  }
  return {bridgesToDelete, twoConnectedPrimalsToUnion};
}

void mergePath(size_t u, size_t v, std::vector<size_t>& twoConnectedComponentsForest, DisjointSetUnion& twoConnected,
               const std::vector<std::pair<size_t, size_t>>& edges, size_t lcaIteration, std::vector<size_t> lastVisit,
               std::vector<size_t>& iRet)
{
  auto r = lca(u, v, twoConnectedComponentsForest, twoConnected, edges, lcaIteration, lastVisit);
  const auto& [bridgesToDelete, twoConnectedPrimalsToUnion] = r;

  for (auto idx : bridgesToDelete) {
    iRet[idx] = false;
  }
  for (auto twoConnectedPrimal : twoConnectedPrimalsToUnion) {
    twoConnected.unionSets(u, twoConnectedPrimal);
  }
}
}  // namespace

std::vector<size_t> bridgesNaive(size_t n, const std::vector<std::pair<size_t, size_t>>& edges)
{
  size_t allComponents = numberOfComponentsBFS(n, edges);
  std::vector<size_t> ret;
  for (size_t idx = 0; idx < edges.size(); ++idx) {
    auto edgesCurr = edges;
    edgesCurr.erase(edgesCurr.begin() + idx);
    size_t componentsCurr = numberOfComponentsBFS(n, edgesCurr);
    if (allComponents + 1 == componentsCurr) {
      ret.push_back(idx);
    }
  }
  return ret;
}

std::vector<size_t> bridgesDisjointSetUnion(size_t n, const std::vector<std::pair<size_t, size_t>>& edges)
{
  std::vector<size_t> iRet(edges.size(), false);
  DisjointSetUnion connected(n);
  DisjointSetUnion twoConnected(n);
  std::vector<size_t> twoConnectedComponentsForest(n, edges.size() + 1);  // indexed by two connected primals
  std::vector<size_t> twoConnectedComponentsForestSizes(n, 1);            // indexed by connected primals
  size_t lcaIteration = 0;
  std::vector<size_t> lastVisit;

  for (size_t idx = 0; idx < edges.size(); ++idx) {
    auto [u, v] = edges[idx];
    size_t uPrimeTwoConnected = twoConnected.findSet(u);
    size_t vPrimeTwoConnected = twoConnected.findSet(v);
    if (uPrimeTwoConnected == vPrimeTwoConnected) {
      continue;
    }
    size_t uPrimeConnected = connected.findSet(u);
    size_t vPrimeConnected = connected.findSet(v);
    if (uPrimeConnected != vPrimeConnected)  // new bridge
    {
      iRet[idx] = true;
      connected.unionSets(uPrimeConnected, vPrimeConnected);
      size_t parent = uPrimeTwoConnected;
      size_t child = vPrimeTwoConnected;
      if (twoConnectedComponentsForestSizes[uPrimeConnected] < twoConnectedComponentsForestSizes[vPrimeConnected]) {
        std::swap(parent, child);
        twoConnectedComponentsForestSizes[vPrimeConnected] += twoConnectedComponentsForestSizes[uPrimeConnected];
      } else {
        twoConnectedComponentsForestSizes[uPrimeConnected] += twoConnectedComponentsForestSizes[vPrimeConnected];
      }
      makeRoot(child, twoConnectedComponentsForest, twoConnected, edges);
      twoConnectedComponentsForest[child] = idx;
    } else  // two connected fusion
    {
      mergePath(uPrimeTwoConnected, vPrimeTwoConnected, twoConnectedComponentsForest, twoConnected, edges, lcaIteration,
                lastVisit, iRet);
    }
  }
  std::vector<size_t> ret;
  ret.reserve(edges.size());
  for (size_t idx = 0; idx < iRet.size(); ++idx) {
    if (iRet[idx]) {
      ret.push_back(idx);
    }
  }
  return ret;
}
#endif  // APPLICATIONS_GRAPHS_BRIDGES_INCLUDED
