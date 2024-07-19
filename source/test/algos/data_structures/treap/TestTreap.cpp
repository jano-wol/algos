#include <gmock/gmock.h>

#include <algorithm>
#include <functional>
#include <limits>
#include <random>
#include <vector>

#include "./../../../../algos/data_structures/treap/implicit_treap.h"
#include "./../../../../algos/data_structures/treap/implicit_treap_naive.h"

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

template <typename T>
void checkTreaps(ImplicitTreap<T> t1, ImplicitTreapNaive<T> t2)
{
  EXPECT_EQ(t1.size(), t2.size());
  for (size_t i = 0; i < t1.size(); ++i) {
    EXPECT_EQ(t1[i], t2[i]);
  }
}

template <typename T>
void checkTreapVec(ImplicitTreap<T>& t, std::vector<T>& v)
{
  EXPECT_EQ(t.size(), v.size());
  int idx = 0;
  for (auto tN : t) {
    EXPECT_EQ(tN, v[idx]);
    ++idx;
  }

  idx = int(v.size()) - 1;
  for (auto rit = t.rbegin(); rit != t.rend(); ++rit) {
    EXPECT_EQ(*rit, v[idx]);
    idx--;
  }
}

template <typename T>
void checkParentsImpl(algos::implicit_treap_utils::Node<T>* curr, algos::implicit_treap_utils::Node<T>* parent)
{
  if (!curr) {
    return;
  }
  if (curr->p != parent) {
    EXPECT_EQ(0, 1);
  }
  checkParentsImpl(curr->l, curr);
  checkParentsImpl(curr->r, curr);
}

template <typename T>
void checkParents(ImplicitTreap<T>& t)
{
  typename ImplicitTreap<T>::Iterator it = t.begin();
  if (it->p == nullptr) {
    EXPECT_EQ(t.begin(), t.end());
    return;
  }
  while (it->p->p != nullptr) {
    it = typename ImplicitTreap<T>::Iterator(it->p);
  }
  checkParentsImpl(it.operator->(), it->p);
}

template <typename T>
void checkTreapsRef(ImplicitTreap<T>& t1, ImplicitTreapNaive<T>& t2)
{
  EXPECT_EQ(t1.size(), t2.size());
  for (size_t i = 0; i < t1.size(); ++i) {
    EXPECT_EQ(t1[i], t2[i]);
  }
}

template <typename T>
ImplicitTreap<T> getRandomTreap(const std::vector<T>& v)
{
  return ImplicitTreap(v);
}

template <typename T>
ImplicitTreapNaive<T> getRandomTreapNaive(const std::vector<T>& v)
{
  return ImplicitTreapNaive(v);
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
      t1.insert(pos, val);
      t2.insert(pos, val);
    } else {
      t1.erase(pos);
      t2.erase(pos);
    }
  }
  t1.push_back(0);
  t2.push_back(0);
  checkTreaps(t1, t2);
  checkTreapsRef(t1, t2);
  EXPECT_NE(t1.size(), 0);
  ImplicitTreap<T> t3;
  ImplicitTreapNaive<T> t4;
  t3 = t1;
  t4 = t2;
  checkTreaps(t3, t4);
  t3.push_back(0);
  t4.push_back(0);
  checkTreaps(t3, t4);
  t3 = t1;
  t4 = t2;
  checkTreaps(t3, t4);
  t3.push_back(0);
  t4.push_back(0);
  EXPECT_NE(t3.size(), t1.size());
  EXPECT_NE(t4.size(), t2.size());

  auto v = getRandomVec(t1.size());
  auto tr1 = getRandomTreap(v);
  auto tr2 = getRandomTreapNaive(v);
  checkTreaps(tr1, tr2);
  auto v2 = getRandomVec(t1.size());
  tr1 = getRandomTreap(v2);
  tr2 = getRandomTreapNaive(v2);
  checkTreaps(tr1, tr2);
  checkTreaps(std::move(t1), std::move(t2));
  EXPECT_EQ(t1.size(), 0);
  checkTreaps(t1, t2);
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

void callRandomItTests(size_t n)
{
  auto v = getRandomVec(n);
  ImplicitTreap<int> t(v);
  if (t.size() > 0) {
    EXPECT_NE(t.begin(), t.end());
  } else {
    EXPECT_EQ(t.begin(), t.end());
  }

  std::mt19937 e;
  checkTreapVec(t, v);
  checkParents(t);
  auto s = v.size();
  for (size_t idx = 0; idx < s; ++idx) {
    int pos = ((v.size() > 0) ? (e() % v.size()) : 0);
    t.erase(pos);
    v.erase(v.begin() + pos);
    checkTreapVec(t, v);
    checkParents(t);
  }
  EXPECT_EQ(t.begin(), t.end());
  checkParents(t);
  std::vector<int> w;
  for (size_t idx = 0; idx < n; ++idx) {
    int pos = ((w.size() > 0) ? (e() % w.size()) : 0);
    int val = e() % 100;
    t.insert(pos, val);
    w.insert(w.begin() + pos, val);
    checkTreapVec(t, w);
    checkParents(t);
  }
  checkParents(t);
  s = w.size();
  for (size_t idx = 0; idx < s; ++idx) {
    int pos = ((w.size() > 0) ? (e() % w.size()) : 0);
    t.erase(pos);
    w.erase(w.begin() + pos);
    checkTreapVec(t, w);
    checkParents(t);
  }
  EXPECT_EQ(t.begin(), t.end());
  checkParents(t);
  for (size_t idx = 0; idx < n; ++idx) {
    int pos = ((w.size() > 0) ? (e() % w.size()) : 0);
    int val = e() % 100;
    t.insert(pos, val);
    w.insert(w.begin() + pos, val);
    checkTreapVec(t, w);
    checkParents(t);
  }
  checkParents(t);
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
  t.insert(0, 6);
  tNaive.insert(0, 6);
  EXPECT_EQ(t.size(), 2);
  EXPECT_EQ(tNaive.size(), 2);
  EXPECT_EQ(t[0], 6);
  EXPECT_EQ(tNaive[0], 6);
  EXPECT_EQ(t[1], 5);
  EXPECT_EQ(tNaive[1], 5);
  t.insert(0, 7);
  tNaive.insert(0, 7);
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
  tLarge.insert(10, 5);
  EXPECT_EQ(tLarge.size(), 100001);
  EXPECT_EQ(tLarge[10], 5);
  tLarge[10] = 6;
  EXPECT_EQ(tLarge[10], 6);

  for (size_t i = 0; i < 66; ++i) {
    callRandomTests(i);
  }
}

TEST(Treap, TestImplicitTreapIterator)
{
  ImplicitTreap<int> t;
  EXPECT_EQ(t.begin(), t.end());
  std::vector<int> init{3, 4, 5, 5, 6, 5, 4, 3, 8};
  std::vector<int> rev{8, 3, 4, 5, 6, 5, 5, 4, 3};
  std::vector<int> zero{0, 0, 0, 0, 0, 0, 0, 0, 0};
  ImplicitTreap<int> t2(init);
  std::vector<int> testVec;
  for (auto v : t2) {
    testVec.push_back(v);
  }
  checkParents(t2);
  EXPECT_EQ(init, testVec);
  testVec.clear();
  std::reverse(t2.begin(), t2.end());
  for (auto v : t2) {
    testVec.push_back(v);
  }
  EXPECT_EQ(rev, testVec);
  testVec.clear();
  for (auto& v : t2) {
    v = 0;
  }
  for (auto v : t2) {
    testVec.push_back(v);
  }
  EXPECT_EQ(zero, testVec);
  for (auto v : testVec) {
    (void)v;
    t2.erase(0);
  }
  EXPECT_EQ(t2.begin(), t2.end());
  t2.push_back(0);
  EXPECT_NE(t2.begin(), t2.end());
  checkParents(t2);
  for (size_t i = 0; i < 66; ++i) {
    callRandomItTests(i);
  }
}
