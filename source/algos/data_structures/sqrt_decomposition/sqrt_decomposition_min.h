#ifndef ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_MIN_INCLUDED
#define ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_MIN_INCLUDED

#include <vector>

template <typename T>
class SqrtDecompositionMin
{
public:
  // runtime = O(n), memory = O(n), where n = |a|.
  SqrtDecompositionMin(std::vector<T> a_)
      : n(a_.size()), len(size_t(sqrt(n + .0)) + 1), a(std::move(a_)), blockMins(len), blockValue(len), blockMonotone(len, false)
  {
    size_t i = 0;
    size_t j = 0;
    for (; i < (n / len); ++i) {
      blockMins[i] = a[i * len];
      j = i * len + 1;
      for (; j < (i + 1) * len; ++j) {
        blockMins[i] = std::min(blockMins[i], a[j]);
      }
    }
    if (j + 1 < n) {
      blockMins[i] = a[j];
      ++j;
      for (; j < n; ++j) {
        blockMins[i] = std::min(blockMins[i], a[j]);
      }
    }
  }

  SqrtDecompositionMin(size_t n_) : SqrtDecompositionMin(std::vector<T>(n_)) {}

  // runtime = O(sqrt(n)), memory = O(1).
  T min(size_t l, size_t r) const
  {
    rangeCheck(l, r);
    T minVal = 0;
    size_t c_l = l / len;
    size_t c_r = r / len;
    if (c_l == c_r) {
      if (blockMonotone[c_l]) {
        minVal = blockValue[c_l];
      } else {
        minVal = a[l];
        for (size_t i = l + 1; i <= r; ++i) minVal = std::min(minVal, a[i]);
      }
    } else {
      if (blockMonotone[c_l]) {
        minVal = blockValue[c_l];
      } else {
        minVal = a[l];
        for (size_t i = l + 1, end = (c_l + 1) * len - 1; i <= end; ++i) minVal = std::min(minVal, a[i]);
      }
      for (size_t i = c_l + 1; i < c_r; ++i) {
        minVal = std::min(blockMins[i], minVal);
      }
      if (blockMonotone[c_r]) {
        minVal = std::min(blockValue[c_r], minVal);
      } else {
        for (size_t i = c_r * len; i <= r; ++i) {
          minVal = std::min(minVal, a[i]);
        }
      }
    }
    return minVal;
  }

  // runtime = O(sqrt(n)), memory = O(1).
  void set(size_t l, size_t r, T val)
  {
    rangeCheck(l, r);
    size_t c_l = l / len;
    size_t c_r = r / len;
    if (c_l == c_r) {
      if (blockMonotone[c_l]) {
        blockMonotone[c_l] = false;
        for (size_t i = c_l * len; i + 1 < std::min((c_l + 1) * len + 1, n); ++i) {
          a[i] = val;
        }
      }
      blockMonotone[c_l] = false;
      for (size_t i = l; i <= r; ++i) {
        a[i] = val;
      }
      blockMins[c_l] = std::min(blockMins[c_l], val);
    } else {
      if (blockMonotone[c_l]) {
        blockMonotone[c_l] = false;
        for (size_t i = l, end = (c_l + 1) * len - 1; i <= end; ++i) {
          a[i] = val;
        }
      }
      blockMonotone[c_l] = false;
      for (size_t i = l, end = (c_l + 1) * len - 1; i <= end; ++i) {
        a[i] = val;
      }
      blockMins[c_l] = std::min(blockMins[c_l], val);

      for (size_t i = c_l + 1; i < c_r; ++i) {
        blockMonotone[i] = true;
        blockValue[i] = val;
        blockMins[i] = val;
      }
      if (blockMonotone[c_r]) {
        blockMonotone[c_r] = false;
        for (size_t i = c_r * len; i <= r; ++i) {
          a[i] = val;
        }
      }
      blockMonotone[c_r] = false;
      for (size_t i = c_r * len; i <= r; ++i) {
        a[i] = val;
      }
      blockMins[c_r] = std::min(blockMins[c_r], val);
    }
  }

private:
  size_t n;
  size_t len;
  std::vector<T> a;
  std::vector<T> blockMins;
  std::vector<T> blockValue;
  std::vector<bool> blockMonotone;

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

#endif  // ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_MIN_INCLUDED
