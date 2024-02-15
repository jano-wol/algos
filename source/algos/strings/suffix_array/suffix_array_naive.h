#ifndef ALGOS_STRINGS_SUFFIX_ARRAY_NAIVE_INCLUDED
#define ALGOS_STRINGS_SUFFIX_ARRAY_NAIVE_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

class SuffixArrayNaive
{
public:
  static std::vector<size_t> suffixArray(const std::string& str)
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
};

#endif  // ALGOS_STRINGS_SUFFIX_ARRAY_NAIVE_INCLUDED
