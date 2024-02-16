#include <gmock/gmock.h>

#include "./../../../algos/strings/suffix_automaton/suffix_automaton.h"

void dfsAutomaton(int idx, const std::vector<SuffixAutomaton::Node>& nodes, size_t& numberOfStates)
{
  for (auto n : nodes[idx].linking) {
    dfsAutomaton(n, nodes, numberOfStates);
  }
  ++numberOfStates;
}

void testSizes(const std::string& str, size_t expected)
{
  SuffixAutomaton automaton(str);
  size_t numberOfStates = 0;
  dfsAutomaton(0, automaton.getNodes(), numberOfStates);
  size_t size = automaton.getNodes().size();
  EXPECT_EQ(size, expected);
  EXPECT_EQ(numberOfStates, expected);
}


TEST(SuffixAutomaton, TestSuffixAutomaton)
{
  testSizes("banana", 10);
  testSizes("", 1);
  testSizes("a", 2);
  testSizes("aa", 3);
  testSizes("ab", 3);
  testSizes("aba", 4);
  testSizes("abb", 5);
}

TEST(SuffixAutomaton, TestSuffixAutomatonUtilities)
{
  SuffixAutomaton automaton("aaababbbab");
  const auto& nodes = automaton.getNodes();
  for (size_t idx = 0; idx < nodes.size(); ++idx) {
    auto endPoses = automaton.getEndPoses(idx);
    const auto& [high, low] = automaton.getStringInterval(idx);
    std::cout << "idx = " << idx << " {";
    for (auto p : endPoses) {
      std::cout << p << " ";
    }
    std::cout << "} ";
    std::cout << high << " " << low << "\n";
  }
}
