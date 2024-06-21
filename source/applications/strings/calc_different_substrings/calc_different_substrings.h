#ifndef APPLICATIONS_STRINGS_CALC_DIFFERENT_SUBSTRINGS_INCLUDED
#define APPLICATIONS_STRINGS_CALC_DIFFERENT_SUBSTRINGS_INCLUDED

#include <algorithm>
#include <set>
#include <string>
#include <unordered_set>
#include <vector>

#include "./../../../algos/strings/kasai/kasai.h"
#include "./../../../algos/strings/string_hash/string_hash.h"
#include "./../../../algos/strings/suffix_automaton/suffix_automaton.h"

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

// runtime = O(n * log(n)), memory = O(n), where n = |str|.
size_t calcDifferentSubstringsKasai(const std::string& str)
{
  auto result = Kasai::kasai(str);
  size_t allSubString = (str.size() * (str.size() + 1)) / 2;
  size_t lcpSum = 0;
  for (auto lcp : result.second) {
    lcpSum += lcp;
  }

  return allSubString - lcpSum;
}

// runtime = O(n), memory = O(n), where n = |str|.
size_t calcDifferentSubstringsAutomaton(const std::string& str)
{
  SuffixAutomaton automaton(str);
  const auto& nodes = automaton.getNodes();
  size_t ret = 0;
  for (size_t i = 1; i < nodes.size(); ++i) {
    ret += nodes[i].len - nodes[nodes[i].link].len;
  }
  return ret;
}

// Stochastic algorithm. runtime = O(n^2), memory = O(n^2), where n = |str|.
size_t calcDifferentSubstringsHash(const std::string& str)
{
  size_t n = str.size();
  const auto& [hashes, hashParams] = StringHash::prefixHashes(str);
  const auto& [pPow, m] = hashParams;
  size_t ret = 0;
  for (size_t length = 1; length <= n; length++) {
    std::unordered_set<uint64_t> hs;
    for (size_t start = 0; start <= n - length; ++start) {
      uint64_t currHash = StringHash::calcSubstringDelatedHash(start, start + length, hashes, pPow, m);
      hs.insert(currHash);
    }
    ret += hs.size();
  }
  return ret;
}

#endif  // APPLICATIONS_STRINGS_CALC_DIFFERENT_SUBSTRINGS_INCLUDED
