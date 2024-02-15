#ifndef ALGOS_STRINGS_Z_FUNCTION_NAIVE_INCLUDED
#define ALGOS_STRINGS_Z_FUNCTION_NAIVE_INCLUDED

#include <iostream>
#include <string>
#include <vector>

class ZFunctionNaive
{
public:
  template <typename T>
  static std::vector<size_t> zFunction(const T& str)
  {
    size_t n = str.size();
    std::vector<size_t> z(n, 0);
    for (size_t i = 0; i < n; i++) {
      size_t intersect = 0;
      while (i + intersect < n && str[i + intersect] == str[intersect]) {
        ++intersect;
      }
      z[i] = intersect;
    }
    return z;
  }
};

#endif  // ALGOS_STRINGS_Z_FUNCTION_NAIVE_INCLUDED
