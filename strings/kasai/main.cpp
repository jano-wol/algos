#include <algorithm>
#include <iostream>
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

int main()
{
  std::string str = "banana";
  auto result = Kasai::kasai(str);
  auto resultNaive = naiveKasai(str);

  for (auto a : result) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  for (auto a : resultNaive.second) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}