#ifndef ALGOS_DATA_STRUCTURES_SPARSE_TABLE_MIN_INCLUDED
#define ALGOS_DATA_STRUCTURES_SPARSE_TABLE_MIN_INCLUDED

#include <vector>

template <typename T>
class SparseTableMin
{
public:
  // runtime = O(n log(n)), memory = O(n log(n)), where n = |v|.
  SparseTableMin(const std::vector<T>& v)
  {
    n = v.size() + 1;
    k = log2Floor(n);

    data.resize(k + 1);
    for (auto& vec : data) {
      vec.resize(n);
    }

    std::copy(v.begin(), v.end(), data[0].begin());
    for (size_t i = 1; i <= k; ++i) {
      for (size_t j = 0; j + (1 << i) <= n; ++j) {
        data[i][j] = std::min(data[i - 1][j], data[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  // runtime = O(1), memory = O(1).
  T query(size_t l, size_t r)
  {
    if (r < l) {
      throw std::overflow_error("incorrect query");
    }
    if (n - 1 <= r) {
      throw std::overflow_error("incorrect query");
    }
    int i = log2Floor(r - l + 1);
    T min = std::min(data[i][l], data[i][r - (1 << i) + 1]);
    return min;
  }

private:
  size_t n;
  size_t k;
  std::vector<std::vector<T>> data;

  int log2Floor(uint64_t i) { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
};

#endif  // ALGOS_DATA_STRUCTURES_SPARSE_TABLE_MIN_INCLUDED
