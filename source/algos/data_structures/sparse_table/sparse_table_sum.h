#ifndef ALGOS_DATA_STRUCTURES_SPARSE_TABLE_SUM_INCLUDED
#define ALGOS_DATA_STRUCTURES_SPARSE_TABLE_SUM_INCLUDED

#include <vector>

template <typename T>
class SparseTableSum
{
public:
  // runtime = O(n log(n)), memory = O(n log(n)), where n = |v|.
  SparseTableSum(const std::vector<T>& v)
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
        data[i][j] = data[i - 1][j] + data[i - 1][j + (1 << (i - 1))];
      }
    }
  }

  // runtime = O(log(n)), memory = O(1).
  T query(size_t l, size_t r) const
  {
    if (r < l) {
      throw std::out_of_range("incorrect query");
    }
    if (n - 1 <= r) {
      throw std::out_of_range("incorrect query");
    }
    T sum = 0;
    for (int i = k; i >= 0; --i) {
      if ((1 << i) <= int64_t(r - l + 1)) {
        sum += data[i][l];
        l += (1 << i);
      }
    }
    return sum;
  }

private:
  size_t n;
  size_t k;
  std::vector<std::vector<T>> data;

  int log2Floor(uint64_t i) const { return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1; }
};

#endif  // ALGOS_DATA_STRUCTURES_SPARSE_TABLE_SUM_INCLUDED
