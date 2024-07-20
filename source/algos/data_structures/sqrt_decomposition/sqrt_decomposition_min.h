#ifndef ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_MIN_INCLUDED
#define ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_MIN_INCLUDED

#include <optional>
#include <vector>

template <typename T>
class SqrtDecompositionMin
{
public:
  // runtime = O(n), memory = O(n), where n = |a|.
  SqrtDecompositionMin(std::vector<T> a_)
      : n(a_.size()), len(size_t(sqrt(n + .0)) + 1), a(std::move(a_)), blockMins(len), blockValue(len)
  {
    for (size_t i = 0; i < (n + len - 1) / len; ++i) {
      blockMins[i] = *(std::min_element(a.begin() + i * len, a.begin() + getBlockEnd(i)));
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
      setTruncateBlock(c_l, l, r + 1, val);
      return;
    }
    setTruncateBlock(c_l, l, (c_l + 1) * len, val);
    for (size_t i = c_l + 1; i < c_r; ++i) {
      blockValue[i] = val;
      blockMins[i] = val;
    }
    setTruncateBlock(c_r, c_r * len, r + 1, val);
  }

private:
  size_t n;
  size_t len;
  std::vector<T> a;
  std::vector<T> blockMins;
  std::vector<std::optional<T>> blockValue;

  void rangeCheck(size_t l, size_t r) const
  {
    if (r < l) {
      throw std::out_of_range("incorrect query");
    }
    if (n <= r) {
      throw std::out_of_range("incorrect query");
    }
  }

  T getMinimum(size_t blockIdx, size_t start, size_t end) const
  {
    if (blockValue[blockIdx]) {
      return *blockValue[blockIdx];
    } else {
      return *(std::min_element(a.begin() + start, a.begin() + end));
    }
  }

  size_t getBlockEnd(size_t blockIdx) const { return std::min((blockIdx + 1) * len, n); }

  void breakBlock(size_t blockIdx)
  {
    if (blockValue[blockIdx]) {
      for (size_t i = blockIdx * len; i < getBlockEnd(blockIdx); ++i) {
        a[i] = (*blockValue[blockIdx]);
      }
      blockValue[blockIdx] = std::nullopt;
    }
  }

  void setTruncateBlock(size_t blockIdx, size_t start, size_t end, T val)
  {
    breakBlock(blockIdx);
    for (size_t i = start; i < end; ++i) {
      a[i] = val;
    }
    blockMins[blockIdx] = getMinimum(blockIdx, blockIdx * len, getBlockEnd(blockIdx));
  }
};

#endif  // ALGOS_DATA_STRUCTURE_SQRT_DECOMPOSITION_MIN_INCLUDED
