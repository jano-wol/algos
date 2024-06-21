#ifndef ALGOS_DATA_STRUCTURES_SEGMENT_TREE_INCLUDED
#define ALGOS_DATA_STRUCTURES_SEGMENT_TREE_INCLUDED

#include <functional>
#include <optional>
#include <vector>

template <typename T, typename Q>
class SegmentTree
{
public:
  struct SegmentTreeNode
  {
    size_t l;
    size_t r;
    Q answer;
    std::optional<T> mod;
  };

  // runtime = O(n * beta), memory = O(n * gamma), where canonicAnswer, compositeAnswers and SegmentTreeNode constructor
  // calls are in O(beta), and the size of SegmentTreeNode is in O(gamma). Typically beta=1, gamma=1.
  SegmentTree(
      const std::vector<T>& a, std::function<Q(const T&)> canonicAnswer_,
      std::function<Q(const Q&, const Q&)> compositeAnswers_,
      std::function<Q(const SegmentTreeNode&)> modA_ = [](const SegmentTreeNode&) -> Q { throw("no modify"); },
      std::function<T(const T&, const T&)> cumulateMods_ = [](const T&, const T&) -> T { throw("no modify"); })
      : n(a.size()),
        canonicAnswer(std::move(canonicAnswer_)),
        compositeAnswers(std::move(compositeAnswers_)),
        getModifiedAnswer(std::move(modA_)),
        cumulateMods(std::move(cumulateMods_))
  {
    t.resize(4 * n);
    if (!a.empty()) {
      build(a, 1, 0, n - 1);
    }
  }

  // runtime = O(log(n) * beta), memory = O(1), where compositeAnswers, getModifiedAnswer,
  // cumulateMods calls are in O(beta). Typically beta=1.
  Q query(size_t l, size_t r)
  {
    rangeCheck(l, r);
    return queryImpl(1, 0, n - 1, l, r);
  }

  // runtime = O(log(n) * beta), memory = O(1), where compositeAnswers, getModifiedAnswer,
  // cumulateMods calls are in O(beta). Typically beta=1.
  void modify(size_t l, size_t r, const T& val)
  {
    rangeCheck(l, r);
    modifyImpl(1, 0, n - 1, l, r, val);
  }

private:
  size_t n;
  std::vector<SegmentTreeNode> t;
  std::function<Q(const T&)> canonicAnswer;
  std::function<Q(const Q&, const Q&)> compositeAnswers;
  std::function<Q(const SegmentTreeNode&)> getModifiedAnswer;
  std::function<T(const T&, const T&)> cumulateMods;

  void rangeCheck(size_t l, size_t r) const
  {
    if (r < l) {
      throw std::overflow_error("incorrect query");
    }
    if (n <= r) {
      throw std::overflow_error("incorrect query");
    }
  }

  void build(const std::vector<T>& a, size_t v, size_t currL, size_t currR)
  {
    if (currL == currR) {
      t[v] = {currL, currR, canonicAnswer(a[currL]), std::nullopt};
    } else {
      size_t tm = (currL + currR) / 2;
      build(a, v * 2, currL, tm);
      build(a, v * 2 + 1, tm + 1, currR);
      t[v] = {currL, currR, compositeAnswers(t[v * 2].answer, t[v * 2 + 1].answer), std::nullopt};
    }
  }

  Q queryImpl(size_t v, size_t currL, size_t currR, size_t l, size_t r)
  {
    if (t[v].mod) {
      push(v);
    }
    if (currL > currR || currL > r || l > currR) {
      return {};
    }
    if (l <= currL && currR <= r) {
      return t[v].answer;
    }
    size_t tm = (currL + currR) / 2;
    Q q1 = queryImpl(v * 2, currL, tm, l, r);
    Q q2 = queryImpl(v * 2 + 1, tm + 1, currR, l, r);
    return compositeAnswers(q1, q2);
  }

  void modifyImpl(size_t v, size_t currL, size_t currR, size_t l, size_t r, const T& val)
  {
    if (t[v].mod) {
      push(v);
    }
    if (currL > currR || currL > r || l > currR) {
      return;
    }
    if (l <= currL && currR <= r) {
      t[v].mod = val;
      push(v);
    } else {
      size_t tm = (currL + currR) / 2;
      modifyImpl(v * 2, currL, tm, l, r, val);
      modifyImpl(v * 2 + 1, tm + 1, currR, l, r, val);
      t[v].answer = compositeAnswers(t[v * 2].answer, t[v * 2 + 1].answer);
    }
  }

  void push(size_t v)
  {
    if (t[v].l != t[v].r) {
      std::vector<size_t> children{v * 2, v * 2 + 1};
      for (auto child : children) {
        if (t[child].mod) {
          t[child].mod = cumulateMods(*t[child].mod, *t[v].mod);
        } else {
          t[child].mod = t[v].mod;
        }
      }
    }
    t[v].answer = getModifiedAnswer(t[v]);
    t[v].mod = std::nullopt;
  }
};

#endif  // ALGOS_DATA_STRUCTURES_SEGMENT_TREE_INCLUDED
