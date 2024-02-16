#ifndef ALGOS_STRINGS_MANACHER_INCLUDED
#define ALGOS_STRINGS_MANACHER_INCLUDED

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Manacher
{
public:
  // runtime = O(n), memory = O(n), where n = |str|.
  static std::pair<std::vector<size_t>, std::vector<size_t>> manacher(const std::string& str)
  {
    if (str.empty()) {
      return {{}, {}};
    }
    std::vector<uint8_t> input(str.begin(), str.end());
    checkInput(input);
    std::vector<uint8_t> t;
    t.reserve(2 * input.size() + 1);
    for (auto c : input) {
      t.push_back(2);
      t.push_back(c);
    }
    t.push_back(2);
    auto res = manacherOdd(t);
    std::vector<size_t> odd;
    std::vector<size_t> even;
    odd.reserve(str.size());
    even.reserve(str.size());
    for (int i = 0; i < res.size() - 1; ++i) {
      if (i & 1 == 0) {
        even.push_back((res[i] - 1) / 2);
      } else {
        odd.push_back(res[i] / 2);
      }
    }
    return {odd, even};
  }

private:
  static void checkInput(const std::vector<uint8_t>& input)
  {
    for (auto i : input) {
      if (i < 3) {
        throw std::invalid_argument("input cannot contain 0, 1 and 2 characters");
      }
    }
  }

  static std::vector<size_t> manacherOdd(const std::vector<uint8_t>& input)
  {
    int n = input.size();
    std::vector<uint8_t> preparedInput;
    preparedInput.reserve(input.size() + 2);
    preparedInput.push_back(0);
    preparedInput.insert(preparedInput.end(), input.begin(), input.end());
    preparedInput.push_back(1);
    std::vector<size_t> ret(n + 2);
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++) {
      ret[i] = std::max(0, std::min(r - i, int(ret[l + (r - i)])));
      while (preparedInput[i - ret[i]] == preparedInput[i + ret[i]]) {
        ret[i]++;
      }
      if (i + ret[i] > r) {
        l = i - ret[i], r = i + ret[i];
      }
    }
    return std::vector<size_t>(ret.begin() + 1, ret.end() - 1);
  }
};

#endif  // ALGOS_STRINGS_MANACHER_INCLUDED
