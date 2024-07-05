#include <gmock/gmock.h>

#include <functional>
#include <limits>
#include <random>
#include <vector>

#include "./../../../../algos/data_structures/treap/implicit_treap.h"
#include "./../../../../algos/data_structures/treap/implicit_treap_naive.h"

template <typename T>
void checkTreaps(ImplicitTreap<T>& t1, ImplicitTreapNaive<T>& t2)
{
  EXPECT_EQ(t1.size(), t2.size());
  for (size_t i = 0; i < t1.size(); ++i) {
    EXPECT_EQ(t1[i], t2[i]);
  }
}

template <typename T>
void testRandomCommands(ImplicitTreap<T>& t1, ImplicitTreapNaive<T>& t2)
{
  std::mt19937 e;
  for (size_t comm = 0; comm < 150; ++comm) {
    checkTreaps(t1, t2);
    size_t type = e() % 4;
    size_t pos = t1.size() > 0 ? e() % t1.size() : 0;
    T val = e() % 100;
    if (type == 0 || t1.size() == 0) {
      t1.push_back(val);
      t2.push_back(val);
    } else if (type == 1) {
      t1.insert(val, pos);
      t2.insert(val, pos);
    } else {
      t1.erase(pos);
      t2.erase(pos);
    }
  }
}

std::vector<int> getRandomVec(size_t n)
{
  std::mt19937 e;
  std::vector<int> ret;
  for (size_t i = 0; i < n; ++i) {
    int val = e() % 100;
    ret.push_back(val);
  }
  return ret;
}

void callRandomTests(size_t n)
{
  ImplicitTreap<int> t11;
  ImplicitTreapNaive<int> t12;
  testRandomCommands(t11, t12);
  ImplicitTreap<int> t21(n);
  ImplicitTreapNaive<int> t22(n);
  testRandomCommands(t21, t22);
  auto v = getRandomVec(n);
  ImplicitTreap<int> t31(v);
  ImplicitTreapNaive<int> t32(v);
  testRandomCommands(t31, t32);
}

TEST(Treap, TestImplicitTreap)
{
  ImplicitTreap<int> t;
  ImplicitTreapNaive<int> tNaive;
  EXPECT_EQ(t.size(), 0);
  EXPECT_EQ(tNaive.size(), 0);
  t.push_back(5);
  tNaive.push_back(5);
  EXPECT_EQ(t.size(), 1);
  EXPECT_EQ(tNaive.size(), 1);
  EXPECT_EQ(t[0], 5);
  EXPECT_EQ(tNaive[0], 5);
  t.insert(6, 0);
  tNaive.insert(6, 0);
  EXPECT_EQ(t.size(), 2);
  EXPECT_EQ(tNaive.size(), 2);
  EXPECT_EQ(t[0], 6);
  EXPECT_EQ(tNaive[0], 6);
  EXPECT_EQ(t[1], 5);
  EXPECT_EQ(tNaive[1], 5);
  t.insert(7, 0);
  tNaive.insert(7, 0);
  EXPECT_EQ(t.size(), 3);
  EXPECT_EQ(tNaive.size(), 3);
  EXPECT_EQ(t[0], 7);
  EXPECT_EQ(tNaive[0], 7);
  EXPECT_EQ(t[1], 6);
  EXPECT_EQ(tNaive[1], 6);
  EXPECT_EQ(t[2], 5);
  EXPECT_EQ(tNaive[2], 5);
  t.erase(2);
  tNaive.erase(2);
  EXPECT_EQ(t.size(), 2);
  EXPECT_EQ(tNaive.size(), 2);
  EXPECT_EQ(t[0], 7);
  EXPECT_EQ(tNaive[0], 7);
  EXPECT_EQ(t[1], 6);
  EXPECT_EQ(tNaive[1], 6);
  t.push_back(8);
  tNaive.push_back(8);
  EXPECT_EQ(t[0], 7);
  EXPECT_EQ(tNaive[0], 7);
  EXPECT_EQ(t[1], 6);
  EXPECT_EQ(tNaive[1], 6);
  EXPECT_EQ(t[2], 8);
  EXPECT_EQ(tNaive[2], 8);
  t.erase(0);
  tNaive.erase(0);
  EXPECT_EQ(t[0], 6);
  EXPECT_EQ(tNaive[0], 6);
  EXPECT_EQ(t[1], 8);
  EXPECT_EQ(tNaive[1], 8);
  ImplicitTreap<int> tLarge(100000);
  EXPECT_EQ(tLarge.size(), 100000);
  tLarge.insert(5, 10);

  for (size_t i = 0; i < 66; ++i) {
    callRandomTests(i);
  }
}