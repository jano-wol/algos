#ifndef ALGOS_DATA_STRUCTURES_SORTED_TREE_INCLUDED
#define ALGOS_DATA_STRUCTURES_SORTED_TREE_INCLUDED

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
  size_t lIdx = 0;
  size_t rIdx = 0;
  size_t retIdx = 0;
  bool lEnd = (lIdx == l.size());
  bool rEnd = (rIdx == r.size());
  std::vector<T> ret(l.size() + r.size());
  while (!lEnd || !rEnd) {
    if (lEnd) {
      std::copy(r.begin() + rIdx, r.end(), ret.begin() + retIdx);
      break;
    }
    if (rEnd) {
      std::copy(l.begin() + lIdx, l.end(), ret.begin() + retIdx);
      break;
    }
    if (l[lIdx] > r[rIdx]) {
      ret[retIdx] = r[rIdx];
      ++rIdx;
      ++retIdx;
    } else {
      ret[retIdx] = l[lIdx];
      ++lIdx;
      ++retIdx;
    }
    lEnd = (lIdx == l.size());
    rEnd = (rIdx == r.size());
  }
  return ret;
}
}  // namespace

template <typename T>
class SortedTree : public SegmentTree<T, std::vector<T>>
{
public:
  using ST = SegmentTree<T, std::vector<T>>;
  using Node = typename ST::SegmentTreeNode;
  SortedTree(const std::vector<T>& a, std::function<std::vector<T>(const Node&)> getModifiedAnswer_,
             std::function<T(const T&, const T&)> cumulateMods_)
      : ST(a, canonicAnswer_<T>, compositeAnswers_<T>, std::move(getModifiedAnswer_), std::move(cumulateMods_))
  {}
};

#endif  // ALGOS_DATA_STRUCTURES_SORTED_TREE_INCLUDED
