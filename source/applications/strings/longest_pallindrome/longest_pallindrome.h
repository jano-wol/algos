#ifndef APPLICATIONS_STRINGS_LONGEST_PALLINDROME_INCLUDED
#define APPLICATIONS_STRINGS_LONGEST_PALLINDROME_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include "./../../../algos/strings/string_hash/string_hash.h"

std::pair<size_t, size_t> longestPallindromeNaive(const std::string& str)
{
  if (str.empty()) {
    return {0, 0};
  }
  auto n = str.size();
  size_t longestPallindromeLength = 1;
  std::pair<size_t, size_t> longestPallindromeInterval = {0, 1};
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + longestPallindromeLength + 1; j <= n; ++j) {
      size_t currLength = j - i;
      auto curr = str.substr(i, currLength);
      bool isPallindrome = true;
      for (size_t k = 0; k <= currLength / 2; ++k) {
        if (curr[k] != curr[currLength - 1 - k]) {
          isPallindrome = false;
          break;
        }
      }
      if (isPallindrome) {
        longestPallindromeLength = j - i;
        longestPallindromeInterval = {i, j};
      }
    }
  }
  return longestPallindromeInterval;
}

// runtime = O(n), memory = O(n), where n = |str|.
/* std::vector<size_t> prefixFreq(const std::string& str)
{
  if (str.empty()) {
    return {};
  }
  auto n = str.size();
  std::vector<size_t> ret(n + 1);
  auto pi = PrefixFunction::prefixFunction(str);
  for (int i = 0; i < int(n); i++) ret[pi[i]]++;
  for (int i = n - 1; i > 0; i--) ret[pi[i - 1]] += ret[i];
  for (int i = 0; i <= int(n); i++) ret[i]++;
  ret.erase(ret.begin());
  return ret;
}
 */
#endif  // APPLICATIONS_STRINGS_LONGEST_PALLINDROME_INCLUDED
