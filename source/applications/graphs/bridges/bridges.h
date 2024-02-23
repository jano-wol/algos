#ifndef APPLICATIONS_GRAPHS_BRIDGES_INCLUDED
#define APPLICATIONS_GRAPHS_BRIDGES_INCLUDED

#include "./../../../algos/data_structures/disjoint_set_union/disjoint_set_union.h"
#include "./../number_of_components/number_of_components.h"

namespace
{
size_t getOtherSide(size_t v, size_t edgeIdx, DisjointSetUnion& twoConnected,
                    const std::vector<std::pair<size_t, size_t>>& edges)
{
  const auto& [p, q] = edges[edgeIdx];
  size_t pPrimal = twoConnected.findSet(p);
  size_t qPrimal = twoConnected.findSet(q);
  size_t primal = ((pPrimal == v) ? qPrimal : pPrimal);
  return primal;
}

void makeRoot(size_t v, std::vector<size_t>& twoConnectedComponentsForest, DisjointSetUnion& twoConnected,
              const std::vector<std::pair<size_t, size_t>>& edges)
{
  size_t childValue = twoConnectedComponentsForest[v];
  while (childValue != edges.size()) {
    v = getOtherSide(v, childValue, twoConnected, edges);
    std::swap(childValue, twoConnectedComponentsForest[v]);
  }
}

std::pair<std::pair<std::vector<size_t>, std::vector<size_t>>, size_t> lca(
    size_t u, size_t v, std::vector<size_t>& twoConnectedComponentsForest, DisjointSetUnion& twoConnected,
    const std::vector<std::pair<size_t, size_t>>& edges, size_t lcaIteration, std::vector<size_t> lastVisit)
{
  ++lcaIteration;
  std::vector<size_t> uVertices;
  std::vector<size_t> uEdges;
  std::vector<size_t> vVertices;
  std::vector<size_t> vEdges;
  size_t lca = 0;
  bool uActive = true;
  bool vActive = true;
  while (true) {
    if (uActive) {
      uVertices.push_back(u);
      if (lastVisit[u] == lcaIteration) {
        lca = u;
        break;
      }
      lastVisit[u] = lcaIteration;
      size_t childU = twoConnectedComponentsForest[u];
      if (childU != edges.size()) {
        uEdges.push_back(childU);
        u = getOtherSide(u, childU, twoConnected, edges);
      } else {
        uActive = false;
      }
    }
    if (vActive) {
      vVertices.push_back(v);
      if (lastVisit[v] == lcaIteration) {
        lca = v;
        break;
      }
      lastVisit[v] = lcaIteration;
      size_t childV = twoConnectedComponentsForest[v];
      if (childV != edges.size()) {
        vEdges.push_back(childV);
        v = getOtherSide(v, childV, twoConnected, edges);
      } else {
        vActive = false;
      }
    }
  }
  std::vector<size_t> twoConnectedPrimalsToUnion;
  twoConnectedPrimalsToUnion.reserve(uVertices.size() + vVertices.size());
  std::vector<size_t> bridgesToDelete;
  bridgesToDelete.reserve(uEdges.size() + vEdges.size());
  size_t idx = 0;
  for (auto uV : uVertices) {
    twoConnectedPrimalsToUnion.push_back(uV);
    if (uV == lca) {
      break;
    }
    bridgesToDelete.push_back(uEdges[idx]);
    ++idx;
  }
  idx = 0;
  for (auto vV : vVertices) {
    if (vV == lca) {
      break;
    }
    twoConnectedPrimalsToUnion.push_back(vV);
    bridgesToDelete.push_back(vEdges[idx]);
    ++idx;
  }
  return {{twoConnectedPrimalsToUnion, bridgesToDelete}, twoConnectedComponentsForest[lca]};
}

void mergePath(size_t u, size_t v, std::vector<size_t>& twoConnectedComponentsForest, size_t uPrimeConnected,
               std::vector<size_t>& twoConnectedComponentsForestSizes, DisjointSetUnion& twoConnected,
               const std::vector<std::pair<size_t, size_t>>& edges, size_t lcaIteration, std::vector<size_t> lastVisit,
               std::vector<bool>& iRet)
{
  auto r = lca(u, v, twoConnectedComponentsForest, twoConnected, edges, lcaIteration, lastVisit);
  const auto& [twoConnectedPrimalsToUnion, bridgesToDelete] = r.first;
  for (auto idx : bridgesToDelete) {
    iRet[idx] = false;
  }
  for (auto twoConnectedPrimal : twoConnectedPrimalsToUnion) {
    twoConnected.unionSets(u, twoConnectedPrimal);
  }
  size_t primal = twoConnected.findSet(u);
  twoConnectedComponentsForest[primal] = r.second;
  twoConnectedComponentsForestSizes[uPrimeConnected] -= (twoConnectedPrimalsToUnion.size() - 1);
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
  DisjointSetUnion connected(n);
  DisjointSetUnion twoConnected(n);
  std::vector<bool> iRet(edges.size(), false);
  std::vector<size_t> twoConnectedComponentsForest(n, edges.size());
  std::vector<size_t> twoConnectedComponentsForestSizes(n, 1);
  std::vector<size_t> lastVisit(n);
  size_t lcaIteration = 0;
  for (size_t idx = 0; idx < edges.size(); ++idx) {
    auto [u, v] = edges[idx];
    size_t uPrimeTwoConnected = twoConnected.findSet(u);
    size_t vPrimeTwoConnected = twoConnected.findSet(v);
    if (uPrimeTwoConnected == vPrimeTwoConnected) {
      continue;
    }
    size_t uPrimeConnected = connected.findSet(u);
    size_t vPrimeConnected = connected.findSet(v);
    if (uPrimeConnected != vPrimeConnected) {
      iRet[idx] = true;
      connected.unionSets(uPrimeConnected, vPrimeConnected);
      size_t parent = uPrimeTwoConnected;
      size_t child = vPrimeTwoConnected;
      size_t uSize = twoConnectedComponentsForestSizes[uPrimeConnected];
      size_t vSize = twoConnectedComponentsForestSizes[vPrimeConnected];
      if (uSize < vSize) {
        std::swap(parent, child);
      }
      makeRoot(child, twoConnectedComponentsForest, twoConnected, edges);
      twoConnectedComponentsForest[child] = idx;
      twoConnectedComponentsForestSizes[connected.findSet(child)] = uSize + vSize;
    } else {
      mergePath(uPrimeTwoConnected, vPrimeTwoConnected, twoConnectedComponentsForest, uPrimeConnected,
                twoConnectedComponentsForestSizes, twoConnected, edges, lcaIteration, lastVisit, iRet);
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
