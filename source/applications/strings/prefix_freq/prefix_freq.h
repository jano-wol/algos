#ifndef APPLICATIONS_STRINGS_PREFIX_FREQ_INCLUDED
#define APPLICATIONS_STRINGS_PREFIX_FREQ_INCLUDED

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "./../../../algos/strings/prefix_function/prefix_function.h"

std::vector<size_t> prefixFreqNaive(const std::string& str)
{
  if (str.empty()) {
    return {};
  }
  auto n = str.size();
  std::vector<size_t> ret;
  for (size_t i = 1; i <= n; ++i) {
    auto currPrefix = str.substr(0, i);
    size_t r = 0;
    for (size_t j = 0; j < n - i + 1; ++j) {
      auto subString = str.substr(j, i);
      if (currPrefix == subString) {
        ++r;
      }
    }
    ret.push_back(r);
  }
  return ret;
}

// runtime = O(n), memory = O(n), where n = |str|.
std::vector<size_t> prefixFreq(const std::string& str)
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

#endif  // APPLICATIONS_STRINGS_PREFIX_FREQ_INCLUDED
