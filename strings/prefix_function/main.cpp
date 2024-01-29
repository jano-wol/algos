#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "prefix_function.h"

std::vector<size_t> naive(const std::string& str)
{
  size_t n = str.size();
  std::vector<size_t> pi(n);
  for (size_t i = 0; i < n; i++)
    for (size_t k = 0; k <= i; k++)
      if (str.substr(0, k) == str.substr(i - k + 1, k))
        pi[i] = k;
  return pi;
}

size_t naiveCountSubstring(const std::string& str, const std::string& text)
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

size_t countSubstring(const std::string& str, const std::string& text)
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
  auto result = PrefixFunction::prefixFunction(strVec);
  size_t ret = std::count(result.begin() + str.size() + 1, result.end(), str.size());
  return ret;
}

int main()
{
  std::string str = "aabaaab";
  auto result = PrefixFunction::prefixFunction(str);
  auto resultNaive = naive(str);

  for (auto a : result) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  for (auto a : resultNaive) {
    std::cout << a << " ";
  }
  std::cout << "\n";

  str = "ab";
  std::string text = "aaaabababababababbbbbabbbb";
  std::cout << naiveCountSubstring(str, text) << "\n";
  std::cout << countSubstring(str, text) << "\n";
}