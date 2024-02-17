#include <gmock/gmock.h>

#include "./../../../algos/strings/suffix_automaton/suffix_automaton.h"

namespace
{
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

void testAutomaton(const std::string& str)
{
  SuffixAutomaton automaton(str);
  const auto& nodes = automaton.getNodes();

  for (size_t i = 0; i < nodes.size(); ++i) {
    auto endPoses = automaton.getEndPoses(i);
    const auto& [high, low] = automaton.getStringInterval(i);
    if (i == 0) {
      EXPECT_EQ(str.size(), endPoses.size());
      for (size_t idx = 0; idx < str.size(); ++idx) {
        EXPECT_EQ(idx, endPoses[idx]);
      }
      EXPECT_EQ(high, "");
      EXPECT_EQ(low, "");
    } else {
      std::vector<std::string> strings{high, low};
      for (auto curr : strings)
      {
        std::vector<size_t> currEndPoses;
        for (size_t j = 0; j + curr.size() <= str.size(); ++j)
        {
          auto candidate = str.substr(j, curr.size());
          if (candidate == curr)
          {
            currEndPoses.push_back(j + curr.size() - 1);
          }
        }
        EXPECT_EQ(endPoses, currEndPoses);
      }
    }
  }
  // check rest
}

}  // namespace

TEST(SuffixAutomaton, TestSuffixAutomaton)
{
  testSizes("banana", 10);
  testSizes("", 1);
  testSizes("a", 2);
  testSizes("aa", 3);
  testSizes("ab", 3);
  testSizes("aba", 4);
  testSizes("abb", 5);
  testSizes("aaababbbab", 16);
  testSizes("abcccba", 11);
  testAutomaton("banana");
  testAutomaton("");
  testAutomaton("a");
  testAutomaton("aa");
  testAutomaton("ab");
  testAutomaton("aba");
  testAutomaton("abb");
  testAutomaton("aaababbbab");
  testAutomaton("abcccba");
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
