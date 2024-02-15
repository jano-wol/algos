#ifndef ALGOS_STRINGS_SUFFIX_ARRAY_INCLUDED
#define ALGOS_STRINGS_SUFFIX_ARRAY_INCLUDED

#include <iostream>
#include <string>
#include <vector>

class SuffixArray
{
public:
  // runtime = O(n log(n)), memory = O(n), where n = |str|.
  static std::vector<size_t> suffixArray(const std::string& str)
  {
    std::vector<uint8_t> input(str.begin(), str.end());
    if (input.empty()) {
      return {0};
    }
    checkInput(input);
    input.push_back(0);

    size_t n = input.size();
    std::vector<size_t> p;
    std::vector<size_t> c;
    init(p, c, input);

    for (size_t h = 0; (1 << h) < n; ++h) {
      std::vector<size_t> pNew(n);
      std::vector<size_t> cNew(n);
      for (size_t idx = 0; idx < n; ++idx) {
        pNew[idx] = cyclicSub(p[idx], (1 << h), n);
      }

      std::vector<size_t> cnt(n, 0);
      for (auto v : pNew) {
        ++cnt[c[v]];
      }
      for (size_t i = 1; i < n; ++i) {
        cnt[i] += cnt[i - 1];
      }
      for (int i = n - 1; i >= 0; --i) {
        p[--cnt[c[pNew[i]]]] = pNew[i];
      }

      size_t classes = 0;
      cNew[pNew[0]] = classes;
      for (size_t i = 1; i < n; ++i) {
        std::pair<size_t, size_t> cur = {c[p[i]], c[cyclicAdd(p[i], (1 << h), n)]};
        std::pair<size_t, size_t> prev = {c[p[i - 1]], c[cyclicAdd(p[i - 1], (1 << h), n)]};
        if (cur != prev) {
          classes++;
        }
        cNew[p[i]] = classes;
      }
      c.swap(cNew);
    }

    return c;
  }

private:
  static void checkInput(const std::vector<uint8_t>& input)
  {
    for (auto i : input) {
      if (i == 0) {
        throw std::invalid_argument("input has zero character");
      }
    }
  }

  static void init(std::vector<size_t>& p, std::vector<size_t>& c, const std::vector<uint8_t>& input)
  {
    p.resize(input.size());
    c.resize(input.size());
    std::vector<size_t> cnt(256, 0);
    for (auto v : input) {
      ++cnt[v];
    }
    for (size_t i = 1; i < cnt.size(); ++i) {
      cnt[i] += cnt[i - 1];
    }
    for (size_t i = 0; i < input.size(); ++i) {
      p[--cnt[input[i]]] = i;
    }
    size_t classes = 0;
    c[p[0]] = classes;
    for (size_t i = 1; i < input.size(); ++i) {
      if (input[p[i]] != input[p[i - 1]]) {
        classes++;
      }
      c[p[i]] = classes;
    }
  }

  static size_t cyclicSub(size_t a, size_t b, size_t n)
  {
    if (b > n) {
      throw std::overflow_error("too large substraction");
    }
    if (a >= b) {
      return a - b;
    } else {
      return (a + n) - b;
    }
  }

  static size_t cyclicAdd(size_t a, size_t b, size_t n) { return (a + b) % n; }
};
#endif  // ALGOS_STRINGS_SUFFIX_ARRAY_INCLUDED
