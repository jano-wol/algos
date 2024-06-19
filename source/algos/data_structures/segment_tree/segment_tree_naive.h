#ifndef ALGOS_DATA_STRUCTURES_SEGMENT_TREE_NAIVE_INCLUDED
#define ALGOS_DATA_STRUCTURES_SEGMENT_TREE_NAIVE_INCLUDED

#include <functional>
#include <vector>

template <typename T, typename Q>
class SegmentTreeNaive
{
public:  
  SegmentTreeNaive(std::vector<T> a_, std::function<Q(const std::vector<T>&)> f_)
      : a(std::move(a_)), f(std::move(f_)), n(a.size())
  {}

  Q query(size_t l, size_t r) const
  {
    rangeCheck(l, r);
    return f(a);
  }

  void increase(size_t l, size_t r, T val)
  {
    rangeCheck(l, r);
    for (size_t i = l; i <= r; ++i) {
      a[i] += val;
    }
  }

  // runtime = O(log(n)), memory = O(1).
  void overwrite(size_t l, size_t r, T overwrite)
  {
    rangeCheck(l, r);
    for (size_t i = l; i <= r; ++i) {
      a[i] = overwrite;
    }
  }

private:
  std::vector<T> a;
  std::function<Q(const std::vector<T>&)> f;
  size_t n;

  void rangeCheck(size_t l, size_t r) const
  {
    if (r < l) {
      throw std::overflow_error("incorrect query");
    }
    if (n <= r) {
      throw std::overflow_error("incorrect query");
    }
  }
};

#endif  // ALGOS_DATA_STRUCTURES_SEGMENT_TREE_NAIVE_INCLUDED
