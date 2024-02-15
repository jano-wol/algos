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

void testAlignment(const std::string& str)
{
  SuffixAutomaton1 automaton1(str);
  SuffixAutomaton2 automaton2(str);
}

TEST(SuffixAutomaton, TestSuffixAutomaton) { testSizes("banana", 10); }
