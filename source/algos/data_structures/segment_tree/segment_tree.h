#ifndef ALGOS_DATA_STRUCTURES_SEGMENT_TREE_INCLUDED
#define ALGOS_DATA_STRUCTURES_SEGMENT_TREE_INCLUDED

#include <functional>
#include <vector>

template <typename T, typename V, typename Q>
class SegmentTree
{
public:
  struct SegmentTreeNode
  {
    V treeValue;
    T add;
    bool overwriteMarked;
  };

  // runtime = O(n), memory = O(n).
  SegmentTree(const std::vector<T>& a, std::function<SegmentTreeNode(T)> createNode_,
              std::function<SegmentTreeNode(const SegmentTreeNode&, const SegmentTreeNode&)> mergeNodes_,
              std::function<Q(const SegmentTreeNode&)> answerNode_, std::function<Q(Q, Q)> mergeAnswers_)
      : n(a.size()),
        createNode(std::move(createNode_)),
        mergeNodes(std::move(mergeNodes_)),
        answerNode(std::move(answerNode_)),
        mergeAnswers(std::move(mergeAnswers_))
  {
    t.reserve(4 * n);
    if (!a.empty()) {
      build(a, 1, 0, n - 1);
    }
  }

  // runtime = O(log(n)), memory = O(1).
  Q query(size_t l, size_t r) const
  {
    rangeCheck(l, r);
    return queryImpl(1, 0, n - 1, l, r);
  }

  // runtime = O(log(n)), memory = O(1).
  void increase(size_t l, size_t r, T val)
  {
    rangeCheck(l, r);
    increaseImpl(1, 0, n - 1, l, r);
  }

  // runtime = O(log(n)), memory = O(1).
  void overwrite(size_t l, size_t r, T overwrite)
  {
    rangeCheck(l, r);
    overwriteImpl(1, 0, n - 1, l, r);
  }

private:
  size_t n;
  std::vector<SegmentTreeNode> t;
  std::function<SegmentTreeNode(T)> createNode;
  std::function<SegmentTreeNode(const SegmentTreeNode&, const SegmentTreeNode&)> mergeNodes;
  std::function<Q(const SegmentTreeNode&)> answerNode;
  std::function<Q(Q, Q)> mergeAnswers;

  void rangeCheck(size_t l, size_t r) const
  {
    if (r < l) {
      throw std::overflow_error("incorrect query");
    }
    if (n <= r) {
      throw std::overflow_error("incorrect query");
    }
  }

  void build(const std::vector<T>& a, size_t v, size_t tl, size_t tr)
  {
    if (tl == tr) {
      t[v] = createNode(a[tl]);
    } else {
      size_t tm = (tl + tr) / 2;
      build(a, v * 2, tl, tm);
      build(a, v * 2 + 1, tm + 1, tr);
      t[v] = mergeNodes(t[v * 2], t[v * 2 + 1]);
    }
  }

  Q queryImpl(size_t v, size_t tl, size_t tr, size_t l, size_t r) const
  {
    if (l == tl && r == tr) {
      return answerNode(t[v]);
    }
    push(v);
    size_t tm = (tl + tr) / 2;
    Q q1 = queryImpl(v * 2, tl, tm, l, std::min(r, tm));
    Q q2 = queryImpl(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);
    return mergeAnswers(q1, q2);
  }

  void increaseImpl(size_t v, size_t tl, size_t tr, size_t l, size_t r, T add)
  {
    if (l > r)
      return;
    if (l == tl && r == tr) {
      t[v].add += add;
    } else {
      size_t tm = (tl + tr) / 2;
      increaseImpl(v * 2, tl, tm, l, std::min(r, tm), add);
      increaseImpl(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, add);
    }
  }

  void overwriteImpl(size_t v, size_t tl, size_t tr, size_t l, size_t r, T overwrite)
  {
    if (l > r)
      return;
    if (l == tl && r == tr) {
      t[v].treeValue = overwrite;
      t[v].add = 0;
      t[v].overwriteMarked = true;
    } else {
      size_t tm = (tl + tr) / 2;
      push(v);
      increaseImpl(v * 2, tl, tm, l, std::min(r, tm), add);
      increaseImpl(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, add);
    }
  }

  void push(int v)
  {
    if (t[v].marked) {
      t[v * 2].treeValue = t[v * 2 + 1].treeValue = t[v].treeValue;
      t[v * 2].overwriteMarked = t[v * 2 + 1].overwriteMarked = true;
      t[v].overwriteMarked = false;
    }
  }
};

#endif  // ALGOS_DATA_STRUCTURES_SEGMENT_TREE_INCLUDED
