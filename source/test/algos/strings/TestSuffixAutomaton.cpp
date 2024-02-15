#include <gmock/gmock.h>

#include "./../../../algos/strings/suffix_automaton/suffix_automaton_1.h"
#include "./../../../algos/strings/suffix_automaton/suffix_automaton_2.h"

void testSizes(const std::string& str, size_t expected)
{
  SuffixAutomaton1 automaton1(str);
  SuffixAutomaton2 automaton2(str);
  size_t size1 = automaton1.getNodes().size();
  size_t size2 = automaton2.getNodes().size();
  EXPECT_EQ(size1, expected);
  EXPECT_EQ(size2, expected);
}

void dfsAutomaton1(int idx, const std::vector<SuffixAutomaton1::Node>& nodes, size_t& numberOfStates)
{
  for (auto n : nodes[idx].linking) {
    dfsAutomaton1(n, nodes, numberOfStates);
  }
  ++numberOfStates;
}

void dfsAutomaton2(SuffixAutomaton2::Node* cur, size_t& numberOfStates)
{
  for (SuffixAutomaton2::Node* next : cur->linking) {
    dfsAutomaton2(next, numberOfStates);
  }
  ++numberOfStates;
}

void testAlignment(const std::string& str)
{
  SuffixAutomaton1 automaton1(str);
  auto nodes1 = automaton1.getNodes();
  size_t size1 = nodes1.size();
  SuffixAutomaton2 automaton2(str);
  auto nodes2 = automaton2.getNodes();
  size_t size2 = nodes2.size();
  EXPECT_EQ(size1, size2);
  for (size_t i = 0; i < size1; ++i) {
    EXPECT_EQ(nodes1[i].len, nodes2[i].len);
    EXPECT_EQ(nodes1[i].next.size(), nodes2[i].next.size());
  }
  size_t numberOfStates1 = 0;
  size_t numberOfStates2 = 0;
  dfsAutomaton1(0, nodes1, numberOfStates1);
  dfsAutomaton2(&nodes2[0], numberOfStates2);
  EXPECT_EQ(numberOfStates1, size1);
  EXPECT_EQ(numberOfStates2, size2);
}

TEST(SuffixAutomaton, TestSuffixAutomaton)
{
  testSizes("banana", 10);
  testAlignment("banana");
  testSizes("", 1);
  testAlignment("");
  testSizes("a", 2);
  testAlignment("a");
  testSizes("a", 2);
  testAlignment("a");
  testSizes("aa", 3);
  testAlignment("aa");
  testSizes("ab", 3);
  testAlignment("ab");
  testSizes("aba", 4);
  testAlignment("aba");
  testSizes("abb", 5);
  testAlignment("abb");
  testAlignment("bbbaaabababbabbbaaaaabbbbbb");
  testAlignment("jGjjHG85_???##??###_843");
}
