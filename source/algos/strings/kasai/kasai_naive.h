#ifndef ALGOS_STRINGS_KASAI_NAIVE_INCLUDED
#define ALGOS_STRINGS_KASAI_NAIVE_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

class KasaiNaive
{
public:
  static std::pair<std::vector<size_t>, std::vector<size_t>> kasai(const std::string& str)
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
    for (idx = 0; idx < v.size(); ++idx) {
      p[idx] = v[idx].second;
    }

    for (idx = 1; idx < p.size(); ++idx) {
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
};

#endif  // ALGOS_STRINGS_KASAI_NAIVE_INCLUDED
