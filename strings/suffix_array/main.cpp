#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "suffix_array.h"

std::vector<size_t> naive(const std::string& str)
{
  std::vector<std::pair<std::string, size_t>> v;
  size_t idx = 0;
  for (auto it = str.begin(); it <= str.end(); ++it) {
    std::string temp(it, str.end());
    v.emplace_back(temp, idx);
    ++idx;
  }
  std::sort(v.begin(), v.end());
  std::vector<size_t> ret(str.size() + 1);
  for (size_t idx = 0; idx < v.size(); ++idx) {
    ret[v[idx].second] = idx;
  }
  return ret;
}

int main()
{
  std::string str = "banana";
  auto resultNaive = naive(str);
  auto result = SuffixArray::suffixArray(str);

  for (auto a : resultNaive) {
    std::cout << a << " ";
  }
  std::cout << "\n";
  for (auto a : result) {
    std::cout << a << " ";
  }
  std::cout << "\n";
}