#ifndef ALGOS_DATA_STRUCTURES_SORTED_TREE_INCLUDED
#define ALGOS_DATA_STRUCTURES_SORTED_TREE_INCLUDED

#include <algorithm>

#include "segment_tree.h"

namespace
{
template <typename T>
std::vector<T> canonicAnswer_(const T& t)
{
  return {t};
}

template <typename T>
std::vector<T> compositeAnswers_(const std::vector<T>& l, const std::vector<T>& r)
{
  std::vector<T> ret;
  std::merge(l.begin(), l.end(), r.begin(), r.end(), std::back_inserter(ret));
  return ret;
}
}  // namespace

template <typename T>
class SortedTree : public SegmentTree<T, std::vector<T>>
{
public:
  using ST = SegmentTree<T, std::vector<T>>;
  using Node = typename ST::SegmentTreeNode;
  SortedTree(
      const std::vector<T>& a,
      std::function<std::vector<T>(const Node&)> modA_ = [](const Node&) -> std::vector<T> { throw("no modify"); },
      std::function<T(const T&, const T&)> cumulateMods_ = [](const T&, const T&) -> T { throw("no modify"); })
      : ST(a, canonicAnswer_<T>, compositeAnswers_<T>, {}, std::move(modA_), std::move(cumulateMods_))
  {}
};

#endif  // ALGOS_DATA_STRUCTURES_SORTED_TREE_INCLUDED