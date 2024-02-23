#ifndef APPLICATIONS_GRAPHS_BRIDGES_INCLUDED
#define APPLICATIONS_GRAPHS_BRIDGES_INCLUDED

#include "./../../../algos/graphs/bfs/bfs.h"
#include "./../number_of_components/number_of_components.h"

std::vector<size_t> bridgesNaive(size_t n, const std::vector<std::pair<size_t, size_t>>& edges)
{
  size_t allComponents = numberOfComponentsNaive(n, edges);
  if (allComponents == 0) {
    return {};
  }
  std::vector<size_t> ret;
  for (size_t idx = 0; idx < edges.size(); ++idx) {
    auto edgesCurr = edges;
    edgesCurr.erase(edgesCurr.begin() + idx);
    size_t componentsCurr = numberOfComponentsNaive(n, edgesCurr);
    if (allComponents - 1 == componentsCurr) {
    }
  }
}
#endif  // APPLICATIONS_GRAPHS_BRIDGES_INCLUDED
