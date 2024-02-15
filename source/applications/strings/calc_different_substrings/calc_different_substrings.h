#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "./../../../algos/strings/kasai/kasai.h"
#include "./../../../algos/strings/suffix_automaton/suffix_automaton_1.h"
#include "./../../../algos/strings/suffix_automaton/suffix_automaton_2.h"

using namespace SuffixAutomaton1;

size_t calcDifferentSubstringsNaive(const std::string& str)
{
  std::set<std::string> all;
  for (auto it1 = str.begin(); it1 <= str.end(); ++it1) {
    for (auto it2 = it1 + 1; it2 <= str.end(); ++it2) {
      std::string curr(it1, it2);
      all.insert(curr);
    }
  }
  return all.size();
}

// runtime = O(n log(n)), memory = O(n), where n = |str|.
size_t calcDifferentSubstringsKasai(const std::string& str)
{
  auto result = Kasai::kasai(str);
  /*
    size_t ret = 0;
    // Equivalent but more expressive:
    for (size_t idx = 1; idx < result.first.size(); ++idx) {
      auto add = (str.size()) - result.first[idx] - result.second[idx - 1];
      ret += add;
    }
  */
  size_t allSubString = (str.size() * (str.size() + 1)) / 2;
  size_t lcpSum = 0;
  for (auto lcp : result.second) {
    lcpSum += lcp;
  }

  return allSubString - lcpSum;
}

// runtime = O(n), memory = O(n), where n = |str|.
size_t calcDifferentSubstringsAutomaton1(const std::string& str)
{
  init();
  for (char c : str) {
    extend(c);
  }
  size_t tot = 0;
  for (int i = 1; i < sz; i++) {
    tot += st[i].len - st[st[i].link].len;
  }
  return tot;
}

// runtime = O(n), memory = O(n), where n = |str|.
void dfsAutomaton2(SuffixAutomaton2::Node* cur, size_t& sum)
{
  for (SuffixAutomaton2::Node* next : cur->linking) {
    dfsAutomaton2(next, sum);
  }
  SuffixAutomaton2::Node* prev = cur->link;
  if (prev != 0) {
    sum += cur->len - prev->len;
  }
}

size_t calcDifferentSubstringsAutomaton2(const std::string& str)
{
  SuffixAutomaton2 automaton(str);
  size_t sum = 0;
  dfsAutomaton2(&automaton.data[0], sum);
  return sum;
}
