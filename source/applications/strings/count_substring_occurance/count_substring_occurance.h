#ifndef APPLICATIONS_STRINGS_COUNT_SUBSTRING_OCCURANCE_INCLUDED
#define APPLICATIONS_STRINGS_COUNT_SUBSTRING_OCCURANCE_INCLUDED

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "./../../../algos/strings/prefix_function/prefix_function.h"
#include "./../../../algos/strings/string_hash/string_hash.h"
#include "./../../../algos/strings/z_function/z_function.h"

size_t countSubstringOccuranceNaive(const std::string& str, const std::string& text)
{
  if (str.empty() || text.size() < str.size()) {
    return 0;
  }
  size_t ret = 0;
  for (size_t i = 0; i <= text.size() - str.size(); ++i) {
    auto curr = text.substr(i, str.size());
    if (curr == str) {
      ++ret;
    }
  }
  return ret;
}

// runtime = O(m + n), memory = O(m + n), where m = |str|, n = |text|.
size_t countSubstringOccurancePrefixFunction(const std::string& str, const std::string& text)
{
  if (str.empty()) {
    return 0;
  }
  std::vector<uint8_t> strVec(str.begin(), str.end());
  std::vector<uint8_t> textVec(text.begin(), text.end());
  strVec.push_back(0);
  strVec.insert(strVec.end(), textVec.begin(), textVec.end());
  size_t check = std::count(strVec.begin(), strVec.end(), 0);
  if (check != 1) {
    throw std::invalid_argument("Concatenation failed.");
  }
  auto pi = PrefixFunction::prefixFunction(strVec);
  size_t ret = std::count(pi.begin() + str.size() + 1, pi.end(), str.size());
  return ret;
}

// runtime = O(m + n), memory = O(m + n), where m = |str|, n = |text|.
size_t countSubstringOccuranceZFunction(const std::string& str, const std::string& text)
{
  if (str.empty()) {
    return 0;
  }
  std::vector<uint8_t> strVec(str.begin(), str.end());
  std::vector<uint8_t> textVec(text.begin(), text.end());
  strVec.push_back(0);
  strVec.insert(strVec.end(), textVec.begin(), textVec.end());
  size_t check = std::count(strVec.begin(), strVec.end(), 0);
  if (check != 1) {
    throw std::invalid_argument("Concatenation failed.");
  }
  auto z = ZFunction::zFunction(strVec);
  size_t ret = std::count(z.begin() + str.size() + 1, z.end(), str.size());
  return ret;
}

/* // Stochastic algorithm. runtime = O(m + n), memory = O(m + n), where m = |str|, n = |text|.
size_t countSubstringOccuranceHash(const std::string& str, const std::string& text)
{
  if (str.empty()) {
    return 0;
  }
  size_t n = str.size();
  StringHash::prefixHashes;
  const auto& [hashes, hashParams] = StringHash::prefixHashes(text);
  const auto& [p, m] = hashParams;
  std::vector<uint64_t> p_pow(n + 1);
  p_pow[0] = 1;
  for (size_t i = 1; i < n; i++) {
    p_pow[i] = (p_pow[i - 1] * p) % m;
  }
} */

#endif  // APPLICATIONS_STRINGS_COUNT_SUBSTRING_OCCURANCE_INCLUDED
