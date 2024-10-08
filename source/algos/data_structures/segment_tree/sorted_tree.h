#ifndef ALGOS_DATA_STRUCTURES_SORTED_TREE_INCLUDED
#define ALGOS_DATA_STRUCTURES_SORTED_TREE_INCLUDED

#include <algorithm>

#include "segment_tree.h"

namespace algos::sorted_tree_utils
{
template <typename T>
std::vector<T> canonicAnswer(const T& t)
{
  return {t};
}

template <typename T>
std::vector<T> compositeAnswers(const std::vector<T>& l, const std::vector<T>& r)
{
  std::vector<T> ret;
  std::merge(l.begin(), l.end(), r.begin(), r.end(), std::back_inserter(ret));
  return ret;
}
}  // namespace algos::sorted_tree_utils

template <typename T>
class SortedTree : public SegmentTree<T, std::vector<T>>
{
public:
  using ST = SegmentTree<T, std::vector<T>>;
  using Node = typename ST::SegmentTreeNode;

  // runtime = O(n * log(n)), memory = O(n * log(n)).
  // SegmentTree::query and modify are very expensive to call (n * log(n) a single call), so these should be not
  // used. SegmentTree::t contains valuable information.
  SortedTree(
      const std::vector<T>& a,
      std::function<std::vector<T>(const Node&)> modA_ = [](const Node&) -> std::vector<T> { throw("no modify"); },
      std::function<T(const T&, const T&)> cumulateMods_ = [](const T&, const T&) -> T { throw("no modify"); })
      : ST(a, algos::sorted_tree_utils::canonicAnswer<T>, algos::sorted_tree_utils::compositeAnswers<T>, {},
           std::move(modA_), std::move(cumulateMods_))
  {}
};

#endif  // ALGOS_DATA_STRUCTURES_SORTED_TREE_INCLUDED