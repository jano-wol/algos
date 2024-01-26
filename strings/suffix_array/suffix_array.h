#ifndef ALGOS_STRINGS_SUFFIX_ARRAY_INCLUDED
#define ALGOS_STRINGS_SUFFIX_ARRAY_INCLUDED

#include <iostream>
#include <string>
#include <vector>

class SuffixArray
{
public:
  static std::vector<int> suffixArray(const std::string& str)
  {
    std::vector<uint8_t> input(str.begin(), str.end());
    if (input.empty()) {
      return {};
    }
    checkInput(input);
    input.push_back(0);

    std::vector<size_t> p;
    std::vector<size_t> c;
    init(p, c, input);

    return {};
  }

private:
  static void checkInput(const std::vector<uint8_t>& input)
  {
    std::string context = "SuffixArray";
    for (auto i : input) {
      if (i == 0) {
        std::cerr << "input has zero character! context=" << context << "\n";
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
};
#endif  // ALGOS_STRINGS_SUFFIX_ARRAY_INCLUDED
