#ifndef ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_SUM_INCLUDED
#define ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_SUM_INCLUDED

#include <vector>

template <typename T>
class SqrtDecompositionSum
{
public:
  // runtime = O(n), memory = O(n), where n = |a|.
  SqrtDecompositionSum(std::vector<T> a_)
      : n(a_.size()), len(size_t(sqrt(n + .0)) + 1), a(std::move(a_)), blockSums(len), blockFixes(len)
  {
    for (size_t i = 0; i < n; ++i) {
      blockSums[i / len] += a[i];
    }
  }

  SqrtDecompositionSum(size_t n_) : SqrtDecompositionSum(std::vector<T>(n_)) {}

  // runtime = O(sqrt(n)), memory = O(1).
  T sum(size_t l, size_t r) const
  {
    rangeCheck(l, r);
    T sum = 0;
    size_t c_l = l / len;
    size_t c_r = r / len;
    if (c_l == c_r) {
      for (size_t i = l; i <= r; ++i) sum += (a[i] + blockFixes[i / len]);
      return sum;
    }
    for (size_t i = l; i <= (c_l + 1) * len - 1; ++i) sum += (a[i] + blockFixes[i / len]);
    for (size_t i = c_l + 1; i < c_r; ++i) sum += (blockSums[i]);
    for (size_t i = c_r * len; i <= r; ++i) sum += (a[i] + blockFixes[i / len]);
    return sum;
  }

  // runtime = O(sqrt(n)), memory = O(1).
  void increase(size_t l, size_t r, T val)
  {
    rangeCheck(l, r);
    size_t c_l = l / len;
    size_t c_r = r / len;
    if (c_l == c_r) {
      for (size_t i = l; i <= r; ++i) {
        a[i] += val;
        blockSums[i / len] += val;
      }
      return;
    }
    for (size_t i = l; i <= (c_l + 1) * len - 1; ++i) {
      a[i] += val;
      blockSums[i / len] += val;
    }
    for (size_t i = c_l + 1; i < c_r; ++i) {
      blockSums[i] += T(val * len);
      blockFixes[i] += val;
    }
    for (size_t i = c_r * len; i <= r; ++i) {
      a[i] += val;
      blockSums[i / len] += val;
    }
  }

private:
  size_t n;
  size_t len;
  std::vector<T> a;
  std::vector<T> blockSums;
  std::vector<T> blockFixes;

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

#endif  // ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_SUM_INCLUDED
