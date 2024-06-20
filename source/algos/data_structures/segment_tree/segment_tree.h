#ifndef ALGOS_DATA_STRUCTURES_SEGMENT_TREE_INCLUDED
#define ALGOS_DATA_STRUCTURES_SEGMENT_TREE_INCLUDED

#include <functional>
#include <optional>
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
    std::optional<T> modValue;
  };

  // runtime = O(n * beta), memory = O(n * gamma), where createSimpleNode and createCompositeNode calls are in O(beta),
  // and the size of SegmentTreeNode is in O(gamma). Typically beta=1, gamma=1.
  SegmentTree(const std::vector<T>& a, std::function<SegmentTreeNode(size_t, size_t, const T&)> createSimpleNode_,
              std::function<SegmentTreeNode(size_t, size_t, const SegmentTreeNode&, const SegmentTreeNode&)>
                  createCompositeNode_,
              std::function<Q(const SegmentTreeNode&)> answerSimpleNode_,
              std::function<Q(const Q&, const Q&)> answerCompositeNode_,
              std::function<void(SegmentTreeNode&, const T&)> modifyNode_,
              std::function<T(const T&, const T&)> cumulateMod_)
      : n(a.size()),
        createSimpleNode(std::move(createSimpleNode_)),
        createCompositeNode(std::move(createCompositeNode_)),
        answerSimpleNode(std::move(answerSimpleNode_)),
        answerCompositeNode(std::move(answerCompositeNode_)),
        modifyNode(std::move(modifyNode_)),
        cumulateMod(std::move(cumulateMod_))
  {
    t.resize(4 * n);
    if (!a.empty()) {
      build(a, 1, 0, n - 1);
    }
  }

  // runtime = O(log(n) * beta), memory = O(1), where answerSimpleNode, answerCompositeNode, modifyNode, cumulateMod
  // calls are in O(beta). Typically beta=1.
  Q query(size_t l, size_t r)
  {
    rangeCheck(l, r);
    return queryImpl(1, 0, n - 1, l, r);
  }

  // runtime = O(log(n) * beta), memory = O(1), where createCompositeNode, answerSimpleNode, answerCompositeNode,
  // modifyNode, cumulateMod calls are in O(beta). Typically beta=1.
  void modify(size_t l, size_t r, const T& val)
  {
    rangeCheck(l, r);
    modifyImpl(1, 0, n - 1, l, r, val);
  }

private:
  size_t n;
  std::vector<SegmentTreeNode> t;
  std::function<SegmentTreeNode(size_t, size_t, const T&)> createSimpleNode;
  std::function<SegmentTreeNode(size_t, size_t, const SegmentTreeNode&, const SegmentTreeNode&)> createCompositeNode;
  std::function<Q(const SegmentTreeNode&)> answerSimpleNode;
  std::function<Q(const Q&, const Q&)> answerCompositeNode;
  std::function<void(SegmentTreeNode&, const T&)> modifyNode;
  std::function<T(const T&, const T&)> cumulateMod;

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

  Q queryImpl(size_t v, size_t currL, size_t currR, size_t l, size_t r)
  {
    if (t[v].modValue) {
      push(v);
    }
    if (currL > currR || currL > r || l > currR) {
      return {};
    }
    if (l <= currL && currR <= r) {
      return answerSimpleNode(t[v]);
    }
    size_t tm = (currL + currR) / 2;
    Q q1 = queryImpl(v * 2, currL, tm, l, r);
    Q q2 = queryImpl(v * 2 + 1, tm + 1, currR, l, r);
    return answerCompositeNode(q1, q2);
  }

  void modifyImpl(size_t v, size_t currL, size_t currR, size_t l, size_t r, const T& val)
  {
    if (t[v].modValue) {
      push(v);
    }
    if (currL > currR || currL > r || l > currR) {
      return;
    }
    if (l <= currL && currR <= r) {
      t[v].modValue = val;
      push(v);
    } else {
      size_t tm = (currL + currR) / 2;
      modifyImpl(v * 2, currL, tm, l, r, val);
      modifyImpl(v * 2 + 1, tm + 1, currR, l, r, val);
      t[v] = createCompositeNode(currL, currR, t[v * 2], t[v * 2 + 1]);
    }
  }

  void push(size_t v)
  {
    if (t[v].l != t[v].r) {
      std::vector<size_t> children{v * 2, v * 2 + 1};
      for (auto child : children) {
        if (t[child].modValue) {
          t[child].modValue = cumulateMod(*t[child].modValue, *t[v].modValue);
        } else {
          t[child].modValue = t[v].modValue;
        }
      }
    }
    modifyNode(t[v], *t[v].modValue);
    t[v].modValue = std::nullopt;
  }
};

#endif  // ALGOS_DATA_STRUCTURES_SEGMENT_TREE_INCLUDED
