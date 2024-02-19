#include <gmock/gmock.h>

#include <vector>

#include "./../../../algos/data_structures/sparse_table/sparse_table_sum.h"

namespace
{
template <typename T>
void performSumTest(const std::vector<T>& v)
{
  SparseTableSum t(v);
  for (size_t i = 0; i < v.size(); ++i) {
    for (size_t j = i; j < v.size(); ++j) {
      T sum = 0;
      for (size_t k = i; k <= j; ++k) {
        sum += v[k];
      }
      EXPECT_EQ(t.query(i, j), sum);
    }
  }
}
}  // namespace

TEST(SparseTable, TestSum)
{
  performSumTest(std::vector<int>{});
  performSumTest(std::vector<int64_t>{0});
  performSumTest(std::vector<int64_t>{-1});
  performSumTest(std::vector<int64_t>{2});
  performSumTest(std::vector<int64_t>{-1, -1});
  performSumTest(std::vector<int64_t>{-1, -2, -1});
  performSumTest(std::vector<int64_t>{-1, -8, -1});
  performSumTest(std::vector<int64_t>{-1, 18, -1});
  performSumTest(std::vector<int64_t>{-1, 18, 7, -1});
  performSumTest(std::vector<int64_t>{-1, 18, 7, 101, -1});
  performSumTest(std::vector<int64_t>{-1, 18, 7, 101, -122});
  performSumTest(std::vector<int>{-1, 18, 7, 101, -122, 1221});
  performSumTest(std::vector<int>{-1, 18, 7, 88, 101, -122, 1221});
  performSumTest(std::vector<int>{-1, 18, 7, 88, 101, 0, -122, 1221});
  performSumTest(std::vector<int>{-1, 18, 7, 88, 101, 11, -122, 1221});
  performSumTest(std::vector<int>{-1, 18, 7, 88, 101, 11, 33, -122, 1221});
  performSumTest(std::vector<int>{-1, 18, 7, 88, 101, 11, 33, -122, -44, 1221});
  performSumTest(std::vector<int>{-1, 18, 7, 88, 101, 11, 33, -122, -44, 1221, -1, -1, 44, 11, 15});
  performSumTest(std::vector<int>{-1, 18, 7, 88, 101, 11, 33, -122, -44, 1221, -1, -1, 44, 11, 15, 1});
  performSumTest(std::vector<int>{-1, 18, 7, 88, 101, 11, 33, -122, -44, 1221, -1, -1, 44, 11, 8, -3, 15});
}
