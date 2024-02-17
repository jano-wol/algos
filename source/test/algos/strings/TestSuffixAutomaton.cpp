#include <gmock/gmock.h>

#include "./../../../algos/strings/suffix_automaton/suffix_automaton.h"

namespace
{
bool cmpNodes(const SuffixAutomaton::Node& node1, const SuffixAutomaton::Node& node2)
{
  bool lenAligned = (node1.len == node2.len);
  bool linkAligned = (node1.link == node2.link);
  bool mainAligned = (node1.main == node2.main);
  bool nextAligned = (node1.next == node2.next);
  bool linkingAligned = (node1.linking == node2.linking);
  return (lenAligned && linkAligned && mainAligned && nextAligned && linkingAligned);
}

bool cmpAutomatons(const SuffixAutomaton& automaton1, const SuffixAutomaton& automaton2)
{
  bool nAligned = (automaton1.getN() == automaton2.getN());
  bool lastMainAligned = (automaton1.getLastMain() == automaton2.getLastMain());
  bool strAligned = (automaton1.getStr() == automaton2.getStr());
  const auto& nodes1 = automaton1.getNodes();
  const auto& nodes2 = automaton2.getNodes();
  if (nodes1.size() != nodes2.size()) {
    return false;
  }
  bool nodesAligned = true;
  for (size_t idx = 0; idx < nodes1.size(); ++idx) {
    nodesAligned = (nodesAligned && cmpNodes(nodes1.at(idx), nodes2.at(idx)));
  }
  return (nAligned && lastMainAligned && strAligned && nodesAligned);
}

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

void testOnline(const std::string& str)
{
  SuffixAutomaton automaton1(str);
  SuffixAutomaton automaton2("");
  for (char c : str) {
    automaton2.extend(c);
  }
  EXPECT_TRUE(cmpAutomatons(automaton1, automaton2));
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
      for (auto curr : strings) {
        std::vector<size_t> currEndPoses;
        for (size_t j = 0; j + curr.size() <= str.size(); ++j) {
          auto candidate = str.substr(j, curr.size());
          if (candidate == curr) {
            currEndPoses.push_back(j + curr.size() - 1);
          }
        }
        EXPECT_EQ(endPoses, currEndPoses);
      }
      size_t j = nodes[i].link;
      auto endPosesPrev = automaton.getEndPoses(j);
      const auto& [highPrev, lowPrev] = automaton.getStringInterval(j);
      std::string lowHelp = low;
      lowHelp.erase(0, 1);
      EXPECT_EQ(lowHelp, highPrev);
      if (!highPrev.empty()) {
        EXPECT_NE(endPoses, endPosesPrev);
      }
    }
    for (const auto& [c, j] : nodes[i].next) {
      const auto& [highNext, lowNext] = automaton.getStringInterval(j);
      std::string highCurr = high;
      highCurr.push_back(c);
      auto candidate = highNext.substr(highNext.size() - highCurr.size(), highCurr.size());
      EXPECT_EQ(candidate, highCurr);
    }
    EXPECT_EQ(nodes[i].len, high.size());
    for (auto j : nodes[i].linking) {
      EXPECT_EQ(nodes[j].link, i);
    }
  }
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
  testOnline("banana");
  testOnline("");
  testOnline("a");
  testOnline("aa");
  testOnline("ab");
  testOnline("aba");
  testOnline("abb");
  testOnline("aaababbbab");
  testOnline("abcccba");
  testOnline("bbbaaabababbabbbaaaaabbbbbb");
  testOnline("jGjjHG85_???##??###_843");
  testOnline("bbbaaajGjjHG85_???##??###_843bababbabjGjjHG85_???##??###_843bbaaaaabbbbbb");
  testOnline("bbbaaajGjjHG85_???##??###_843bababbabjGjjHG85_??##??###_843bbaaaaabbbbbb");
  testAutomaton("banana");
  testAutomaton("");
  testAutomaton("a");
  testAutomaton("aa");
  testAutomaton("ab");
  testAutomaton("aba");
  testAutomaton("abb");
  testAutomaton("aaababbbab");
  testAutomaton("abcccba");
  testAutomaton("bbbaaabababbabbbaaaaabbbbbb");
  testAutomaton("jGjjHG85_???##??###_843");
  testAutomaton("bbbaaajGjjHG85_???##??###_843bababbabjGjjHG85_???##??###_843bbaaaaabbbbbb");
  testAutomaton("bbbaaajGjjHG85_???##??###_843bababbabjGjjHG85_??##??###_843bbaaaaabbbbbb");
}
