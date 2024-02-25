#ifndef ALGOS_DATA_STRUCTURES_FENWICK_INCLUDED
#define ALGOS_DATA_STRUCTURES_FENWICK_INCLUDED

#include <vector>

template <typename T>
class Fenwick
{
public:
  Fenwick(size_t n_) : n(n_), bit1(std::vector<T>(n)), bit2(std::vector<T>(n)) {}

  Fenwick(std::vector<T> const& a) : Fenwick(a.size())
  {
    for (size_t i = 0; i < a.size(); ++i) {
      bit1[i] += a[i];
      size_t r = (i | (i + 1));
      if (r < n) {
        bit1[r] += bit1[i];
      }
    }
  }

  T sum(size_t l, size_t r) const
  {
    rangeCheck(l, r);
    return (prefixSum(r) - prefixSum(int(l) - 1));
  }

  void increase(size_t l, size_t r, T val)
  {
    rangeCheck(l, r);
    increase(l, val, bit1);
    increase(r + 1, -val, bit1);
    increase(l, val * T(l), bit2);
    increase(r + 1, -val * T(r + 1), bit2);
  }

private:
  size_t n;
  std::vector<T> bit1;
  std::vector<T> bit2;

  void rangeCheck(size_t l, size_t r) const
  {
    if (r < l) {
      throw std::overflow_error("incorrect query");
    }
    if (n <= r) {
      throw std::overflow_error("incorrect query");
    }
  }

  T sum(int r, const std::vector<T>& bit) const
  {
    T ret = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) ret += bit[r];
    return ret;
  }

  T prefixSum(size_t r) const { return (sum(r, bit1) * (r + 1) - sum(r, bit2)); }

  void increase(int idx, int delta, std::vector<T>& bit)
  {
    for (; idx < int(n); idx = idx | (idx + 1)) bit[idx] += delta;
  }
};

#endif  // ALGOS_DATA_STRUCTURES_FENWICK_INCLUDED
