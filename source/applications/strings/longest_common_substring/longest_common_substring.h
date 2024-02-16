#ifndef APPLICATIONS_STRINGS_LONGEST_COMMON_SUBSTRING_INCLUDED
#define APPLICATIONS_STRINGS_LONGEST_COMMON_SUBSTRING_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

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

#endif  // APPLICATIONS_STRINGS_LONGEST_COMMON_SUBSTRING_INCLUDED
