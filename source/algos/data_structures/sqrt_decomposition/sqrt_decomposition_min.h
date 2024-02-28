#ifndef ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_MIN_INCLUDED
#define ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_MIN_INCLUDED

#include <vector>

template <typename T>
class SqrtDecompositionMin
{
public:
  // runtime = O(n), memory = O(n), where n = |a|.
  SqrtDecompositionMin(std::vector<T> a_)
      : n(a_.size()),
        len(size_t(sqrt(n + .0)) + 1),
        a(std::move(a_)),
        blockMins(len),
        blockValue(len),
        blockMonotone(len)
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
    if (j < n) {
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
    size_t c_l = l / len;
    size_t c_r = r / len;
    if (c_l == c_r) {
      return getMinimum(c_l, l, r + 1);
    }
    T minVal = getMinimum(c_l, l, (c_l + 1) * len);
    for (size_t i = c_l + 1; i < c_r; ++i) {
      minVal = std::min(blockMins[i], minVal);
    }
    T lastBlockMinimum = getMinimum(c_r, c_r * len, r + 1);
    return std::min(minVal, lastBlockMinimum);
  }

  // runtime = O(sqrt(n)), memory = O(1).
  void set(size_t l, size_t r, T val)
  {
    rangeCheck(l, r);
    size_t c_l = l / len;
    size_t c_r = r / len;
    if (c_l == c_r) {
      breakBlock(c_l);
      for (size_t i = l; i <= r; ++i) {
        a[i] = val;
      }
      blockMins[c_l] = getMinimum(c_l, c_l * len, std::min((c_l + 1) * len, n));
      return;
    }
    if (blockMonotone[c_l]) {
      blockMonotone[c_l] = false;
      for (size_t i = c_l * len; i <= (c_l + 1) * len - 1; ++i) {
        a[i] = blockValue[c_l];
      }
    }
    blockMonotone[c_l] = false;
    for (size_t i = l; i <= (c_l + 1) * len - 1; ++i) {
      a[i] = val;
    }
    blockMins[c_l] = a[c_l * len];
    for (size_t i = c_l * len + 1; i <= (c_l + 1) * len - 1; ++i) {
      blockMins[c_l] = std::min(blockMins[c_l], a[i]);
    }

    for (size_t i = c_l + 1; i < c_r; ++i) {
      blockMonotone[i] = true;
      blockValue[i] = val;
      blockMins[i] = val;
    }
    if (blockMonotone[c_r]) {
      blockMonotone[c_r] = false;
      for (size_t i = c_r * len; i < std::min((c_r + 1) * len, n); ++i) {
        a[i] = blockValue[c_r];
      }
    }
    blockMonotone[c_r] = false;
    for (size_t i = c_r * len; i <= r; ++i) {
      a[i] = val;
    }
    blockMins[c_r] = a[c_r * len];
    for (size_t i = c_r * len + 1; i < std::min((c_r + 1) * len, n); ++i) {
      blockMins[c_r] = std::min(blockMins[c_r], a[i]);
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

  T getMinimum(size_t blockIdx, size_t start, size_t end) const
  {
    if (blockMonotone[blockIdx]) {
      return blockValue[blockIdx];
    } else {
      return *(std::min_element(a.begin() + start, a.begin() + end));
    }
  }

  void breakBlock(size_t blockIdx)
  {
    if (blockMonotone[blockIdx]) {
      for (size_t i = blockIdx * len; i < std::min((blockIdx + 1) * len, n); ++i) {
        a[i] = blockValue[blockIdx];
      }
      blockMonotone[blockIdx] = false;
    }
  }
};

#endif  // ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_MIN_INCLUDED
