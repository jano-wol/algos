#ifndef ALGOS_STRINGS_KASAI_INCLUDED
#define ALGOS_STRINGS_KASAI_INCLUDED

#include "./../suffix_array/suffix_array.h"

class Kasai
{
public:
  // runtime = O(n log(n)), memory = O(n), where n = |str|.
  static std::pair<std::vector<size_t>, std::vector<size_t>> kasai(const std::string& str)
  {
    auto suffixArr = SuffixArray::suffixArray(str);
    std::vector<size_t> p(suffixArr.size());
    // Very small inefficiency, not O relevant: p could have been calculated during suffixArray()
    for (size_t idx = 0; idx < suffixArr.size(); ++idx) {
      p[suffixArr[idx]] = idx;
    }

    size_t n = str.size();
    if (n == 0) {
      return {p, {}};
    }

    std::vector<size_t> rank(n + 1, 0);
    for (size_t i = 0; i < n + 1; i++) {
      rank[p[i]] = i;
    }
    int k = 0;
    std::vector<size_t> lcp(n, 0);
    for (size_t i = 0; i < n + 1; i++) {
      if (rank[i] == n) {
        k = 0;
        continue;
      }
      size_t j = p[rank[i] + 1];
      while (i + k < n && j + k < n && str[i + k] == str[j + k]) {
        ++k;
      }
      lcp[rank[i]] = k;
      if (k) {
        --k;
      }
    }
    return {p, lcp};
  }
};

#endif  // ALGOS_STRINGS_KASAI_INCLUDED