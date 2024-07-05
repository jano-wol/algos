#include <gmock/gmock.h>

#include <functional>
#include <limits>
#include <random>
#include <vector>

#include "./../../../../algos/data_structures/treap/implicit_treap.h"
#include "./../../../../algos/data_structures/treap/implicit_treap_naive.h"

/* void testRandomCommands(std::vector<int> init, size_t steps)
{
  size_t n = init.size();
  std::mt19937 e;
  for (int c = 0; c < 4; ++c) {
    auto [st, stn] = createSegmentTrees(c, init);
    for (size_t idx = 0; idx < steps; ++idx) {
      size_t type = e() % 2;
      size_t l = e() % n;
      size_t r = e() % n;
      if (r < l) {
        std::swap(l, r);
      }
      int val = e() % 100;
      if (type == 0 || c == 3) {
        int result = st.query(l, r);
        int resultNaive = stn.query(l, r);
        EXPECT_EQ(result, resultNaive);
      } else {
        st.modify(l, r, val);
        stn.modify(l, r, val);
      }
    }
  }
}
 */
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
}