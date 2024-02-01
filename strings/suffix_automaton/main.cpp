#include <iostream>
#include <set>
#include <string>

#include "../kasai/kasai.h"
#include "suffix_automaton.h"

using namespace SuffixAutomaton;
long long calcDifferentSubstringsAutomaton(const std::string& str)
{
  init();
  for (char c : str) {
    extend(c);
  }
  long long tot = 1;
  for (int i = 1; i < sz; i++) {
    tot += st[i].len - st[st[i].link].len;
  }
  return tot;
}

size_t calcDifferentSubstringsKasai(const std::string& str)
{
  auto result = Kasai::kasai(str);
  size_t ret = 1;
  size_t allSubString = (str.size() * (str.size() + 1)) / 2 + 1;
  size_t lcpSum = 0;
  for (auto lcp : result.second) {
    lcpSum += lcp;
  }

  return allSubString - lcpSum;
}

size_t calcDifferentSubstringsNaive(const std::string& str)
{
  std::set<std::string> all;
  for (auto it1 = str.begin(); it1 <= str.end(); ++it1) {
    for (auto it2 = it1; it2 <= str.end(); ++it2) {
      std::string curr(it1, it2);
      all.insert(curr);
    }
  }
  return all.size();
}

int main()
{
  std::string str =
      "qqqqqqqqqqzrzrrzrzrrzrrzrzrrzrzrrzttttttttttttttttttttttttttttttttttttttttttttttttttttttqncpqzcxpbwa";
  std::cout << calcDifferentSubstringsAutomaton(str) << "\n";
  std::cout << calcDifferentSubstringsKasai(str) << "\n";
  std::cout << calcDifferentSubstringsNaive(str) << "\n";
}
