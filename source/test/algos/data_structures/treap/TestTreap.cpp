#include <gmock/gmock.h>

#include <functional>
#include <limits>
#include <random>
#include <vector>

#include "./../../../../algos/data_structures/treap/implicit_treap.h"

TEST(Treap, TestImplicitTreap)
{
  ImplicitTreap<int> t;
  EXPECT_EQ(t.size(), 0);
  t.insert(0, 5);
  EXPECT_EQ(t.size(), 1);
  EXPECT_EQ(t[0], 5);
  t.insert(0, 6);
  EXPECT_EQ(t.size(), 2);
  EXPECT_EQ(t[0], 6);
  EXPECT_EQ(t[1], 5);
  t.insert(0, 7);
  EXPECT_EQ(t.size(), 3);
  EXPECT_EQ(t[0], 7);
  EXPECT_EQ(t[1], 6);
  EXPECT_EQ(t[2], 5);
  t.erase(2);
  EXPECT_EQ(t.size(), 2);
  EXPECT_EQ(t[0], 7);
  EXPECT_EQ(t[1], 6);
  t.insert(2, 8);
  EXPECT_EQ(t[0], 7);
  EXPECT_EQ(t[1], 6);
  EXPECT_EQ(t[2], 8);
  t.erase(0);
  EXPECT_EQ(t[0], 6);
  EXPECT_EQ(t[1], 8);
  ImplicitTreap<int> tLarge(100000);
  EXPECT_EQ(tLarge.size(), 100000);
  tLarge.insert(5, 10);
}