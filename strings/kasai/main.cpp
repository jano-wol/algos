#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "kasai.h"

std::pair<std::vector<size_t>, std::vector<size_t>> naiveKasai(const std::string& str)
{
  std::vector<std::pair<std::string, size_t>> v;
  size_t idx = 0;
  for (auto it = str.begin(); it <= str.end(); ++it) {
    std::string temp(it, str.end());
    v.emplace_back(temp, idx);
    ++idx;
  }
  std::sort(v.begin(), v.end());
  std::vector<size_t> p(v.size());
  std::vector<size_t> lcp(v.size() == 0 ? 0 : v.size() - 1);
  for (size_t idx = 0; idx < v.size(); ++idx) {
    p[idx] = v[idx].second;
  }

  for (size_t idx = 1; idx < p.size(); ++idx) {
    size_t i = 0;
    for (; i < v[idx].first.size(); ++i) {
      if (v[idx].first[i] != v[idx - 1].first[i]) {
        break;
      }
    }
    lcp[idx - 1] = i;
  }
  return {p, lcp};
}

size_t calcDifferentSubstrings(const std::string& str)
{
  auto result = Kasai::kasai(str);
  size_t ret = 1;
  /*
    // Equivalent but more expressive:
    for (size_t idx = 1; idx < result.first.size(); ++idx) {
      auto add = (str.size()) - result.first[idx] - result.second[idx - 1];
      ret += add;
    }
  */
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
  std::string str = "banana";
  auto result = Kasai::kasai(str);
  auto resultNaive = naiveKasai(str);

  for (auto a : result.second) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  for (auto a : resultNaive.second) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  std::cout << "number of different substrings=" << calcDifferentSubstrings(str) << "\n";
  std::cout << "number of different substrings naive=" << calcDifferentSubstringsNaive(str) << "\n";
}
