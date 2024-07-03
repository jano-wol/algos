#ifndef APPLICATIONS_STRINGS_LONGEST_COMMON_SUBSTRING_INCLUDED
#define APPLICATIONS_STRINGS_LONGEST_COMMON_SUBSTRING_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include "./../../../algos/strings/kasai/kasai.h"
#include "./../../../algos/strings/suffix_automaton/suffix_automaton.h"

std::pair<size_t, std::pair<size_t, size_t>> longestCommonSubstringNaive(const std::string& str1,
                                                                         const std::string& str2)
{
  if (str1.empty() || str2.empty()) {
    return {0, {0, 0}};
  }
  size_t smallerLength = std::min(str1.size(), str1.size());
  int i = smallerLength;
  for (; i >= 0; --i) {
    for (int j = 0; j + i <= int(str1.size()); ++j) {
      auto curr1 = str1.substr(j, i);
      for (int k = 0; k + i <= int(str2.size()); ++k) {
        auto curr2 = str2.substr(k, i);
        if (curr1 == curr2) {
          return {static_cast<size_t>(i), {static_cast<size_t>(j), static_cast<size_t>(k)}};
        }
      }
    }
  }
  return {};
}

// runtime = O((m + n) log(m + n)), memory = O(m + n), where m = |str1|, n = |str2|.
std::pair<size_t, std::pair<size_t, size_t>> longestCommonSubstringKasai(const std::string& str1,
                                                                         const std::string& str2)
{
  if (str1.empty() || str2.empty()) {
    return {0, {0, 0}};
  }
  std::string s = str1;
  s.push_back(char(1));
  s += str2;
  size_t check = std::count(s.begin(), s.end(), 1);
  if (check != 1) {
    throw std::invalid_argument("Concatenation failed.");
  }
  int limit = str1.size();
  const auto& [p, lcp] = Kasai::kasai(s);

  size_t bestLength = 0;
  size_t bestIdx1 = 0;
  size_t bestIdx2 = 0;
  for (size_t idx = 2; idx < lcp.size(); ++idx) {
    int currIdx = p[idx];
    int nextIdx = p[idx + 1];
    if (static_cast<long long>(nextIdx - limit) * static_cast<long long>(currIdx - limit) < 0) {
      if (lcp[idx] > bestLength) {
        bestLength = lcp[idx];
        if (currIdx > limit) {
          bestIdx1 = nextIdx;
          bestIdx2 = currIdx - 1 - limit;
        } else {
          bestIdx1 = currIdx;
          bestIdx2 = nextIdx - 1 - limit;
        }
      }
    }
  }
  return {bestLength, {bestIdx1, bestIdx2}};
}

// runtime = O(m + n), memory = O(m + n), where m = |str1|, n = |str2|.
std::pair<size_t, std::pair<size_t, size_t>> longestCommonSubstringAutomaton(const std::string& str1,
                                                                             const std::string& str2)
{
  if (str1.empty() || str2.empty()) {
    return {0, {0, 0}};
  }
  SuffixAutomaton automaton(str1);
  const auto& nodes = automaton.getNodes();
  size_t v = 0;
  size_t l = 0;
  size_t best = 0;
  size_t bestPos = 0;
  size_t bestV = v;
  for (size_t i = 0; i < str2.size(); i++) {
    while (v && !nodes[v].next.count(str2[i])) {
      v = nodes[v].link;
      l = nodes[v].len;
    }
    if (nodes[v].next.count(str2[i])) {
      v = nodes[v].next.at(str2[i]);
      l++;
    }
    if (l > best) {
      best = l;
      bestPos = i;
      bestV = v;
    }
  }
  auto endPoses = automaton.getEndPoses(bestV);
  return {best, {(endPoses[0] + 1) - best, (bestPos + 1) - best}};
}

#endif  // APPLICATIONS_STRINGS_LONGEST_COMMON_SUBSTRING_INCLUDED
