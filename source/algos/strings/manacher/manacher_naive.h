#ifndef ALGOS_STRINGS_MANACHER_NAIVE_INCLUDED
#define ALGOS_STRINGS_MANACHER_NAIVE_INCLUDED

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class ManacherNaive
{
public:
  static std::pair<std::vector<size_t>, std::vector<size_t>> manacher(const std::string& str)
  {
    std::vector<size_t> odd;
    std::vector<size_t> even;
    for (int i = 0; i < int(str.size()); ++i) {
      int j = 1;
      while (true) {
        if ((i - j < 0) || ((i + j) >= int(str.size()))) {
          break;
        }
        if (str[i - j] != str[i + j]) {
          break;
        }
        ++j;
      }
      odd.push_back(j);
    }

    for (int i = 0; i < int(str.size()); ++i) {
      int j = 0;
      while (true) {
        if ((i - j - 1 < 0) || ((i + j) >= int(str.size()))) {
          break;
        }
        if (str[i - j - 1] != str[i + j]) {
          break;
        }
        ++j;
      }
      even.push_back(j);
    }
    return {odd, even};
  }
};

#endif  // ALGOS_STRINGS_MANACHER_NAIVE_INCLUDED
