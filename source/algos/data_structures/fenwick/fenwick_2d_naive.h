#ifndef ALGOS_DATA_STRUCTURES_FENWICK_2D_NAIVE_INCLUDED
#define ALGOS_DATA_STRUCTURES_FENWICK_2D_NAIVE_INCLUDED

#include <vector>

template <typename T>
class Fenwick2DNaive
{
public:
  Fenwick2DNaive(size_t m_, size_t n_) : m(m_), n(n_), mat(m_, std::vector<T>(n_)) {}
  Fenwick2DNaive(std::vector<std::vector<T>> mat_) : m(mat_.size()), n(m > 0 ? mat_[0].size() : 0), mat(std::move(mat_))
  {}

  T sum(const std::pair<size_t, size_t>& sW, const std::pair<size_t, size_t>& nE) const
  {
    const auto& [s, w] = sW;
    const auto& [no, e] = nE;
    if (no < s || m <= no) {
      throw std::out_of_range("incorrect sum query");
    }
    if (e < w || n <= e) {
      throw std::out_of_range("incorrect sum query");
    }
    T ret = 0;
    for (size_t idx1 = s; idx1 <= no; ++idx1) {
      for (size_t idx2 = w; idx2 <= e; ++idx2) {
        ret += mat[idx1][idx2];
      }
    }
    return ret;
  }

  void increase(const std::pair<size_t, size_t>& sW, const std::pair<size_t, size_t>& nE, T val)
  {
    const auto& [s, w] = sW;
    const auto& [no, e] = nE;
    if (no < s || m <= no) {
      throw std::out_of_range("incorrect sum query");
    }
    if (e < w || n <= e) {
      throw std::out_of_range("incorrect sum query");
    }
    for (size_t idx1 = s; idx1 <= no; ++idx1) {
      for (size_t idx2 = w; idx2 <= e; ++idx2) {
        mat[idx1][idx2] += val;
      }
    }
  }

private:
  size_t m;
  size_t n;
  std::vector<std::vector<T>> mat;
};

#endif  // ALGOS_DATA_STRUCTURES_FENWICK_2D_NAIVE_INCLUDED
