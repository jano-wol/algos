#ifndef ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_MIN_NAIVE_INCLUDED
#define ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_MIN_NAIVE_INCLUDED

#include <vector>

template <typename T>
class SqrtDecompositionMinNaive
{
public:
  SqrtDecompositionMinNaive(size_t n_) : n(n_), v(std::vector<T>(n_)) {}
  SqrtDecompositionMinNaive(std::vector<T> v_) : n(v_.size()), v(std::move(v_)) {}

  T min(size_t l, size_t r) const
  {
    rangeCheck(l, r);
    T ret = v[l];
    for (size_t idx = l + 1; idx <= r; ++idx) {
      ret = std::min(ret, v[idx]);
    }
    return ret;
  }

  void set(size_t l, size_t r, T val)
  {
    rangeCheck(l, r);
    for (size_t idx = l; idx <= r; ++idx) {
      v[idx] = val;
    }
  }

private:
  size_t n;
  std::vector<T> v;

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

#endif  // ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_MIN_NAIVE_INCLUDED
