#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "./../../../algos/strings/prefix_function/prefix_function.h"

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
size_t countSubstringOccurance(const std::string& str, const std::string& text)
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
