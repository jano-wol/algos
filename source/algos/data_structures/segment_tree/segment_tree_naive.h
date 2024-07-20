#ifndef ALGOS_DATA_STRUCTURES_SEGMENT_TREE_NAIVE_INCLUDED
#define ALGOS_DATA_STRUCTURES_SEGMENT_TREE_NAIVE_INCLUDED

#include <functional>
#include <vector>

template <typename T, typename Q>
class SegmentTreeNaive
{
public:
  SegmentTreeNaive(
      std::vector<T> a_, std::function<Q(size_t, size_t, const std::vector<T>&)> queryImpl_,
      std::function<T(const T&, const T&)> modifyImpl_ = [](const T&, const T&) -> T { throw("no modify"); })
      : a(std::move(a_)), queryImpl(std::move(queryImpl_)), modifyImpl(std::move(modifyImpl_)), n(a.size())
  {}

  Q query(size_t l, size_t r) const
  {
    rangeCheck(l, r);
    return queryImpl(l, r, a);
  }

  void modify(size_t l, size_t r, T val)
  {
    rangeCheck(l, r);
    for (size_t i = l; i <= r; ++i) {
      a[i] = modifyImpl(a[i], val);
    }
  }

private:
  std::vector<T> a;
  std::function<Q(size_t, size_t, const std::vector<T>&)> queryImpl;
  std::function<T(const T&, const T&)> modifyImpl;
  size_t n;

  void rangeCheck(size_t l, size_t r) const
  {
    if (r < l) {
      throw std::out_of_range("incorrect query");
    }
    if (n <= r) {
      throw std::out_of_range("incorrect query");
    }
  }
};

#endif  // ALGOS_DATA_STRUCTURES_SEGMENT_TREE_NAIVE_INCLUDED
