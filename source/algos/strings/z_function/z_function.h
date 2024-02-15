#ifndef ALGOS_STRINGS_Z_FUNCTION_INCLUDED
#define ALGOS_STRINGS_Z_FUNCTION_INCLUDED

#include <iostream>
#include <string>
#include <vector>

class ZFunction
{
public:
  // runtime = O(n), memory = O(n), where n = |str|.
  template <typename T>
  static std::vector<size_t> zFunction(const T& str)
  {
    if (str.empty()) {
      return {};
    }
    size_t n = str.size();
    std::vector<size_t> z(n, 0);
    z[0] = n;
    size_t l = 0;
    size_t r = 0;
    for (size_t i = 1; i < n; i++) {
      if (i < r) {
        z[i] = std::min(z[i - l], r - i);
      }
      while (i + z[i] < n && str[i + z[i]] == str[z[i]]) {
        ++z[i];
      }
      if (r < i + z[i]) {
        l = i;
        r = i + z[i];
      }
    }
    return z;
  }
};

#endif  // ALGOS_STRINGS_Z_FUNCTION_INCLUDED
