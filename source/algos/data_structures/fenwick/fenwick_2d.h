#ifndef ALGOS_DATA_STRUCTURES_FENWICK_2D_INCLUDED
#define ALGOS_DATA_STRUCTURES_FENWICK_2D_INCLUDED

#include <vector>

template <typename T>
class Fenwick2D
{
public:
  // runtime = O(m * n), memory = O(m * n).
  Fenwick2D(size_t m_, size_t n_)
      : m(m_),
        n(n_),
        bit1(std::vector<std::vector<T>>(m_, std::vector<T>(n_))),
        bit2(std::vector<std::vector<T>>(m_, std::vector<T>(n_))),
        baseMatrix(false)
  {}

  // runtime = O(m * n), memory = O(m * n).
  Fenwick2D(std::vector<std::vector<T>> const& a) : Fenwick2D(a.size(), ((a.size() == 0) ? 0 : a[0].size()))
  {
    baseMatrix = true;
    bit3 = std::vector<std::vector<T>>(m, std::vector<T>(n));
    for (size_t i = 0; i < m; ++i) {
      for (size_t j = 0; j < n; ++j) {
        bit3[i][j] += a[i][j];
        size_t r = (j | (j + 1));
        if (r < n) {
          bit3[i][r] += bit3[i][j];
        }
      }
    }
  }

  // runtime = O(log(m) * log(n)), memory = O(1).
  T sum(const std::pair<size_t, size_t>& sW, const std::pair<size_t, size_t>& nE) const
  {
    rangeCheck(sW, nE);
    const auto& [s, w] = sW;
    const auto& [no, e] = nE;
    int s_ = int(s) - 1;
    int w_ = int(w) - 1;
    T x = baseMatrix ? (sum(nE, bit3) + sum({s_, w_}, bit3) - sum({no, w_}, bit3) - sum({s_, e}, bit3)) : 0;
    return x + (prefixSum(nE) + prefixSum({s_, w_}) - prefixSum({no, w_}) - prefixSum({s_, e}));
  }

  // runtime = O(log(m) * log(n)), memory = O(1).
  void increase(const std::pair<size_t, size_t>& sW, const std::pair<size_t, size_t>& nE, T val)
  {
    /*     rangeCheck(sW, nE);
        increase(l, val, bit1);
        increase(r + 1, -val, bit1);
        increase(l, val * T(l), bit2);
        increase(r + 1, -val * T(r + 1), bit2); */
  }

private:
  size_t m;
  size_t n;
  std::vector<std::vector<T>> bit1;
  std::vector<std::vector<T>> bit2;
  std::vector<std::vector<T>> bit3;
  bool baseMatrix;

  void rangeCheck(const std::pair<size_t, size_t>& sW, const std::pair<size_t, size_t>& nE) const
  {
    const auto& [s, w] = sW;
    const auto& [no, e] = nE;
    if (no < s || m <= no) {
      throw std::overflow_error("incorrect query");
    }
    if (e < w || n <= e) {
      throw std::overflow_error("incorrect query");
    }
  }

  T sum(const std::pair<size_t, size_t>& p, const std::vector<std::vector<T>>& bit) const
  {
    const auto& [x, y] = p;
    T ret = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
        ret += bit[i][j];
      }
    }
    return ret;
  }

  T prefixSum(const std::pair<size_t, size_t>& p) const { return 0; }

  void increase(const std::pair<size_t, size_t>& p, T delta, std::vector<std::vector<T>>& bit)
  {
    const auto& [x, y] = p;
    for (int i = x; i < m; i = i | (i + 1)) {
      for (int j = y; j < n; j = j | (j + 1)) {
        bit[i][j] += delta;
      }
    }
  }
};

#endif  // ALGOS_DATA_STRUCTURES_FENWICK_2D_INCLUDED
