#ifndef APPLICATIONS_STRINGS_LONGEST_COMMON_SUBSTRING_INCLUDED
#define APPLICATIONS_STRINGS_LONGEST_COMMON_SUBSTRING_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include "./../../../algos/strings/kasai/kasai.h"

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
          return {i, {j, k}};
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
  int currIdx = p[2];
  for (size_t idx = 3; idx < lcp.size() + 1; ++idx) {
    int nextIdx = p[idx];
    if (((nextIdx - limit < 0) && (currIdx - limit > 0)) || ((nextIdx - limit > 0) && (currIdx - limit < 0))) {
      if (lcp[idx - 1] > bestLength) {
        bestLength = lcp[idx - 1];
        if (currIdx > limit) {
          bestIdx1 = nextIdx;
          bestIdx2 = currIdx - 1 - limit;
        } else {
          bestIdx1 = currIdx;
          bestIdx2 = nextIdx - 1 - limit;
        }
      }
    }
    currIdx = nextIdx;
  }
  return {bestLength, {bestIdx1, bestIdx2}};
}

#endif  // APPLICATIONS_STRINGS_LONGEST_COMMON_SUBSTRING_INCLUDED
