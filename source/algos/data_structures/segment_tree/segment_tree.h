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
    size_t l;
    size_t r;
    V treeValue;
    T add;
    bool overwriteMarked;
  };

  // runtime = O(n), memory = O(n).
  SegmentTree(const std::vector<T>& a, std::function<SegmentTreeNode(size_t, size_t, const T&)> createSimpleNode_,
              std::function<SegmentTreeNode(size_t, size_t, const SegmentTreeNode&, const SegmentTreeNode&)>
                  createCompositeNode_,
              std::function<Q(const SegmentTreeNode&)> answerSimpleNode_,
              std::function<Q(const Q&, const Q&)> answerCompositeNode_)
      : n(a.size()),
        createSimpleNode(std::move(createSimpleNode_)),
        createCompositeNode(std::move(createCompositeNode_)),
        answerSimpleNode(std::move(answerSimpleNode_)),
        answerCompositeNode(std::move(answerCompositeNode_))
  {
    t.resize(4 * n);
    if (!a.empty()) {
      build(a, 1, 0, n - 1);
    }
  }

  // runtime = O(log(n)), memory = O(1).
  Q query(size_t l, size_t r)
  {
    rangeCheck(l, r);
    return queryImpl(1, 0, n - 1, l, r);
  }

  // runtime = O(log(n)), memory = O(1).
  void increase(size_t l, size_t r, T val)
  {
    rangeCheck(l, r);
    increaseImpl(1, 0, n - 1, l, r, val);
  }

  // runtime = O(log(n)), memory = O(1).
  void overwrite(size_t l, size_t r, T overwrite)
  {
    rangeCheck(l, r);
    overwriteImpl(1, 0, n - 1, l, r, overwrite);
  }

private:
  size_t n;
  std::vector<SegmentTreeNode> t;
  std::function<SegmentTreeNode(size_t, size_t, const T&)> createSimpleNode;
  std::function<SegmentTreeNode(size_t, size_t, const SegmentTreeNode&, const SegmentTreeNode&)> createCompositeNode;
  std::function<Q(const SegmentTreeNode&)> answerSimpleNode;
  std::function<Q(const Q&, const Q&)> answerCompositeNode;

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
      t[v] = createSimpleNode(tl, tr, a[tl]);
    } else {
      size_t tm = (tl + tr) / 2;
      build(a, v * 2, tl, tm);
      build(a, v * 2 + 1, tm + 1, tr);
      t[v] = createCompositeNode(tl, tr, t[v * 2], t[v * 2 + 1]);
    }
  }

  Q queryImpl(size_t v, size_t tl, size_t tr, size_t l, size_t r)
  {
    if (l > r || tl > tr)
      return {};
    if (l == tl && r == tr) {
      return answerSimpleNode(t[v]);
    }
    push(v);
    size_t tm = (tl + tr) / 2;
    Q q1 = queryImpl(v * 2, tl, tm, l, std::min(r, tm));
    Q q2 = queryImpl(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r);
    return answerCompositeNode(q1, q2);
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
      t[v] = {tl, tr, overwrite, 0, true};
    } else {
      size_t tm = (tl + tr) / 2;
      push(v);
      overwriteImpl(v * 2, tl, tm, l, std::min(r, tm), overwrite);
      overwriteImpl(v * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, overwrite);
    }
  }

  void push(size_t v)
  {
    if (t[v].overwriteMarked) {
      t[v * 2].treeValue = t[v * 2 + 1].treeValue = t[v].treeValue;
      t[v * 2].overwriteMarked = t[v * 2 + 1].overwriteMarked = true;
      t[v].overwriteMarked = false;
    }
  }
};

#endif  // ALGOS_DATA_STRUCTURES_SEGMENT_TREE_INCLUDED
