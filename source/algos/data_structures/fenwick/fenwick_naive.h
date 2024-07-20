#ifndef ALGOS_DATA_STRUCTURES_FENWICK_NAIVE_INCLUDED
#define ALGOS_DATA_STRUCTURES_FENWICK_NAIVE_INCLUDED

#include <vector>

template <typename T>
class FenwickNaive
{
public:
  FenwickNaive(size_t n_) : n(n_), v(std::vector<T>(n_)) {}
  FenwickNaive(std::vector<T> v_) : n(v_.size()), v(std::move(v_)) {}

  T sum(size_t l, size_t r) const
  {
    if (r < l) {
      throw std::out_of_range("incorrect sum query");
    }
    if (n <= r) {
      throw std::out_of_range("incorrect sum query");
    }
    T ret = 0;
    for (size_t idx = l; idx <= r; ++idx) {
      ret += v[idx];
    }
    return ret;
  }

  void increase(size_t l, size_t r, T val)
  {
    if (r < l) {
      throw std::out_of_range("incorrect increase");
    }
    if (n <= r) {
      throw std::out_of_range("incorrect increase");
    }
    for (size_t idx = l; idx <= r; ++idx) {
      v[idx] += val;
    }
  }

private:
  size_t n;
  std::vector<T> v;
};

#endif  // ALGOS_DATA_STRUCTURES_FENWICK_NAIVE_INCLUDED
