#ifndef ALGOS_DATA_STRUCTURES_SPARSE_TABLE_DISJOINT_SUM_INCLUDED
#define ALGOS_DATA_STRUCTURES_SPARSE_TABLE_DISJOINT_SUM_INCLUDED

#include <vector>

template <typename T>
class SparseTableDisjointSum
{
public:
  // runtime = O(n log(n)), memory = O(n log(n)), where n = |v|.
  SparseTableDisjointSum(std::vector<T> v_) : v(std::move(v_))
  {
    n = v.size() + 1;
    maxLevel = log2Floor(n);
    size = n;
    if ((1UL << maxLevel) != n) {
      size = (1 << ++maxLevel);
    }
    data.resize(maxLevel + 1);
    for (auto& vec : data) {
      vec.resize(size);
    }
    if (!v.empty()) {
      build(0, 0, size);
    }
  }

  // runtime = O(1), memory = O(1).
  T query(size_t l, size_t r) const
  {
    if (r < l) {
      throw std::overflow_error("incorrect query");
    }
    if (n - 1 <= r) {
      throw std::overflow_error("incorrect query");
    }
    if (l == r)
      return v[l];
    int k2 = log2Floor(l ^ r);
    int level = maxLevel - 1 - k2;
    T ans = data[level][l];
    if (r & ((1 << k2) - 1))
      ans += data[level][r];
    return ans;
  }

private:
  std::vector<T> v;
  size_t n;
  size_t size;
  size_t maxLevel;
  std::vector<std::vector<T>> data;

  int log2Floor(uint64_t i) const { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
  int log2Ceil(uint64_t i) const
  {
    if (!i) {
      return -1;
    }
    int ret = log2Floor(i);
    if ((i & (i - 1)) == 0) {
      ++ret;
    }
    return ret;
  }

  T getV(size_t i) { return i < v.size() ? v[i] : T{}; }

  void build(size_t level, size_t l, size_t r)
  {
    size_t m = (l + r) / 2;
    data[level][m] = getV(m);
    for (int i = m - 1; i >= int(l); i--) {
      data[level][i] = data[level][i + 1] + getV(i);
    }

    if (m + 1 < r) {
      data[level][m + 1] = getV(m + 1);
      for (size_t i = m + 2; i < r; i++) {
        data[level][i] = data[level][i - 1] + getV(i);
      }
    }
    if (l + 1 != r) {
      build(level + 1, l, m);
      build(level + 1, m, r);
    }
  }
};

#endif  // ALGOS_DATA_STRUCTURES_SPARSE_TABLE_DISJOINT_SUM_INCLUDED
