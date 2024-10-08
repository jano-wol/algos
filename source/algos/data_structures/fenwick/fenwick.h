#ifndef ALGOS_DATA_STRUCTURES_FENWICK_INCLUDED
#define ALGOS_DATA_STRUCTURES_FENWICK_INCLUDED

#include <vector>

template <typename T>
class Fenwick
{
public:
  // runtime = O(n), memory = O(n).
  Fenwick(size_t n_) : n(n_), bit1(std::vector<T>(n)), bit2(std::vector<T>(n)), baseVector(false) {}

  // runtime = O(n), memory = O(n).
  Fenwick(std::vector<T> const& a) : Fenwick(a.size())
  {
    baseVector = true;
    bit3 = a;
    for (size_t i = 0; i < n; ++i) {
      size_t r = (i | (i + 1));
      if (r < n) {
        bit3[r] += bit3[i];
      }
    }
  }

  // runtime = O(log(n)), memory = O(1).
  T sum(size_t l, size_t r) const
  {
    rangeCheck(l, r);
    int l_ = int(l) - 1;
    T x = baseVector ? sumImpl(r, bit3) - sumImpl(l_, bit3) : 0;
    return x + (prefixSum(r) - prefixSum(l_));
  }

  // runtime = O(log(n)), memory = O(1).
  void increase(size_t l, size_t r, T val)
  {
    rangeCheck(l, r);
    increaseImpl(l, 1, T(l), val);
    increaseImpl(r + 1, -1, -T(r + 1), val);
  }

private:
  size_t n;
  std::vector<T> bit1;
  std::vector<T> bit2;
  std::vector<T> bit3;
  bool baseVector;

  void rangeCheck(size_t l, size_t r) const
  {
    if (r < l) {
      throw std::out_of_range("incorrect query");
    }
    if (n <= r) {
      throw std::out_of_range("incorrect query");
    }
  }

  T sumImpl(int r, const std::vector<T>& bit) const
  {
    T ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];
    return ret;
  }

  T prefixSum(size_t r) const { return (sumImpl(r, bit1) * (r + 1) - sumImpl(r, bit2)); }

  void increaseImpl(int idx, T delta1, T delta2, T val)
  {
    for (; idx < int(n); idx = idx | (idx + 1)) {
      bit1[idx] += (delta1 * val);
      bit2[idx] += (delta2 * val);
    }
  }
};

#endif  // ALGOS_DATA_STRUCTURES_FENWICK_INCLUDED
