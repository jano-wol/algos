#ifndef APPLICATIONS_DATA_STRUCTURES_RANGE_SUM_QUERY_INCLUDED
#define APPLICATIONS_DATA_STRUCTURES_RANGE_SUM_QUERY_INCLUDED

#include <algorithm>
#include <memory>
#include <vector>

#include "./../../../algos/data_structures/fenwick/fenwick.h"
#include "./../../../algos/data_structures/mo/mo.h"
#include "./../../../algos/data_structures/segment_tree/segment_tree.h"
#include "./../../../algos/data_structures/sparse_table/sparse_table_disjoint_sum.h"
#include "./../../../algos/data_structures/sparse_table/sparse_table_sum.h"
#include "./../../../algos/data_structures/sqrt_decomposition/sqrt_decomposition_sum.h"

namespace algos::range_sum_query_utils
{
void checkSumQuery(size_t l, size_t r, size_t n)
{
  if (r < l) {
    throw std::overflow_error("invalid query: r < l");
  }
  if (n <= r) {
    throw std::overflow_error("invalid query: n <= r");
  }
}

template <typename T, typename R>
class MoObjectSum : public IMoObject<R>
{
public:
  MoObjectSum(std::vector<T> base_) : sum(0), base(std::move(base_)) {}

  void add(size_t idx) override { sum += base[idx]; };
  void remove(size_t idx) override { sum -= base[idx]; };
  R solve() const override { return sum; };
  size_t getN() const override { return base.size(); };

private:
  R sum;
  std::vector<T> base;
};
}  // namespace algos::range_sum_query_utils

template <typename T>
std::vector<T> rangeSumQueryNaive(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [l, r] : queries) {
    algos::range_sum_query_utils::checkSumQuery(l, r, n);
    T sum = a[l];
    for (size_t i = l + 1; i <= r; ++i) {
      sum += a[i];
    }
    ret.push_back(sum);
  }
  return ret;
}

// runtime = O(n * log(n) + m * log(n)), memory = O(n * log(n)), where n = |a|, m = |queries|. Online algorithm.
template <typename T>
std::vector<T> rangeSumQuerySparseTable(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  SparseTableSum t(a);
  for (const auto& [l, r] : queries) {
    algos::range_sum_query_utils::checkSumQuery(l, r, n);
    T sum = t.query(l, r);
    ret.push_back(sum);
  }
  return ret;
}

// runtime = O(n * log(n) + m * 1), memory = O(n * log(n)), where n = |a|, m = |queries|. Online algorithm.
template <typename T>
std::vector<T> rangeSumQuerySparseTableDisjointSum(const std::vector<T>& a,
                                                   const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  SparseTableDisjointSum t(a);
  for (const auto& [l, r] : queries) {
    algos::range_sum_query_utils::checkSumQuery(l, r, n);
    T sum = t.query(l, r);
    ret.push_back(sum);
  }
  return ret;
}

// runtime = O(n + m * log(n)), memory = O(n + m), where n = |a|, m = |queries|. Online algorithm. Vector a can be
// mutated by Fenwick::increase in O(log(n)) runtime.
template <typename T>
std::vector<T> rangeSumQueryFenwick(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  Fenwick<T> t(a);
  for (const auto& [l, r] : queries) {
    algos::range_sum_query_utils::checkSumQuery(l, r, n);
    T sum = t.sum(l, r);
    ret.push_back(sum);
  }
  return ret;
}

// runtime = O(n + m * sqrt(n)), memory = O(n + m), where n = |a|, m = |queries|. Online algorithm. Vector a can be
// mutated by SqrtDecompositionSum::increase in O(sqrt(n)) runtime.
template <typename T>
std::vector<T> rangeSumQuerySqrtDecomposition(const std::vector<T>& a,
                                              const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  SqrtDecompositionSum<T> d(a);
  std::vector<T> ret;
  ret.reserve(queries.size());
  for (const auto& [l, r] : queries) {
    algos::range_sum_query_utils::checkSumQuery(l, r, n);
    ret.push_back(d.sum(l, r));
  }
  return ret;
}

// runtime = O(n * sqrt(m) + m * log(m)), memory = O(n + m), where n = |a|, m = |queries|.
template <typename T>
std::vector<T> rangeSumQueryMo(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  std::unique_ptr<IMoObject<T>> iMoObjectPtr = std::make_unique<algos::range_sum_query_utils::MoObjectSum<T, T>>(a);
  Mo<T> mo(std::move(iMoObjectPtr));
  return mo.solve(queries);
}

// runtime = O(n + m * log(n)), memory = O(n + m), where n = |a|, m = |queries|. Online algorithm. Vector a can be
// mutated by SegmentTree::modify typically in O(log(n)) runtime. (The precise mutate runtime is stated at modify.)
template <typename T>
std::vector<T> rangeSumQuerySegmentTree(const std::vector<T>& a, const std::vector<std::pair<size_t, size_t>>& queries)
{
  size_t n = a.size();
  std::vector<T> ret;
  ret.reserve(queries.size());
  std::function<int(int)> canonicAnswer = [](int v) { return v; };
  std::function<int(int, int)> compositeAnswers = [](int a1, int a2) { return a1 + a2; };
  SegmentTree<T, T> s(a, std::move(canonicAnswer), std::move(compositeAnswers), 0);
  for (const auto& [l, r] : queries) {
    algos::range_sum_query_utils::checkSumQuery(l, r, n);
    T sum = s.query(l, r);
    ret.push_back(sum);
  }
  return ret;
}

#endif  // APPLICATIONS_DATA_STRUCTURES_RANGE_SUM_QUERY_INCLUDED
