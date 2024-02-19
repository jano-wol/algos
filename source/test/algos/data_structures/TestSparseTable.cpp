#include <gmock/gmock.h>

#include <random>
#include <vector>

#include "./../../../algos/data_structures/sparse_table/sparse_table_disjoint_sum.h"
#include "./../../../algos/data_structures/sparse_table/sparse_table_min.h"
#include "./../../../algos/data_structures/sparse_table/sparse_table_sum.h"

namespace
{
template <typename T>
void performSumTest(const std::vector<T>& v)
{
  SparseTableSum t1(v);
  SparseTableDisjointSum t2(v);
  for (size_t i = 0; i < v.size(); ++i) {
    for (size_t j = i; j < v.size(); ++j) {
      T sum = 0;
      for (size_t k = i; k <= j; ++k) {
        sum += v[k];
      }
      EXPECT_EQ(t1.query(i, j), sum);
      EXPECT_EQ(t2.query(i, j), sum);
    }
  }
}

template <typename T>
void performMinTest(const std::vector<T>& v)
{
  SparseTableMin t(v);
  for (size_t i = 0; i < v.size(); ++i) {
    for (size_t j = i; j < v.size(); ++j) {
      T minVal = v[i];
      for (size_t k = i + 1; k <= j; ++k) {
        minVal = std::min(minVal, v[k]);
      }
      EXPECT_EQ(t.query(i, j), minVal);
    }
  }
}

std::vector<int> generateRandomVector(size_t s)
{
  std::mt19937 e;
  std::vector<int> ret;
  for (size_t i = 0; i < s; ++i) {
    int r = e() % 1000;
    r -= 500;
    ret.push_back(r);
  }
  return ret;
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
  for (size_t i = 0; i < 130; ++i) {
    auto v = generateRandomVector(i);
    performSumTest(v);
  }
}

TEST(SparseTable, TestMin)
{
  performMinTest(std::vector<int>{});
  performMinTest(std::vector<int64_t>{0});
  performMinTest(std::vector<int64_t>{-1});
  performMinTest(std::vector<int64_t>{2});
  performMinTest(std::vector<int64_t>{-1, -1});
  performMinTest(std::vector<int64_t>{-1, -2, -1});
  performMinTest(std::vector<int64_t>{-1, -8, -1});
  performMinTest(std::vector<int64_t>{-1, 18, -1});
  performMinTest(std::vector<int64_t>{-1, 18, 7, -1});
  performMinTest(std::vector<int64_t>{-1, 18, 7, 101, -1});
  performMinTest(std::vector<int64_t>{-1, 18, 7, 101, -122});
  performMinTest(std::vector<int>{-1, 18, 7, 101, -122, 1221});
  performMinTest(std::vector<int>{-1, 18, 7, 88, 101, -122, 1221});
  performMinTest(std::vector<int>{-1, 18, 7, 88, 101, 0, -122, 1221});
  performMinTest(std::vector<int>{-1, 18, 7, 88, 101, 11, -122, 1221});
  performMinTest(std::vector<int>{-1, 18, 7, 88, 101, 11, 33, -122, 1221});
  performMinTest(std::vector<int>{-1, 18, 7, 88, 101, 11, 33, -122, -44, 1221});
  performMinTest(std::vector<int>{-1, 18, 7, 88, 101, 11, 33, -122, -44, 1221, -1, -1, 44, 11, 15});
  performMinTest(std::vector<int>{-1, 18, 7, 88, 101, 11, 33, -122, -44, 1221, -1, -1, 44, 11, 15, 1});
  performMinTest(std::vector<int>{-1, 18, 7, 88, 101, 11, 33, -122, -44, 1221, -1, -1, 44, 11, 8, -3, 15});
  for (size_t i = 0; i < 130; ++i) {
    auto v = generateRandomVector(i);
    performMinTest(v);
  }
}
