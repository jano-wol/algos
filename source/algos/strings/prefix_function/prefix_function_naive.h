#ifndef ALGOS_STRINGS_PREFIX_FUNCTION_NAIVE_INCLUDED
#define ALGOS_STRINGS_PREFIX_FUNCTION_NAIVE_INCLUDED

#include <string>
#include <vector>

class PrefixFunctionNaive
{
public:
  template <typename T>
  static std::vector<size_t> prefixFunction(const T& str)
  {
    size_t n = str.size();
    std::vector<size_t> pi(n);
    for (size_t i = 0; i < n; ++i) {
      for (size_t j = 0; j <= i; ++j) {
        bool eq = true;
        for (size_t k = 0; k < j; ++k) {
          if (str[k] != str[i - j + 1 + k]) {
            eq = false;
            break;
          }
        }
        if (eq) {
          pi[i] = j;
        }
      }
    }
    return pi;
  }
};
#endif  // ALGOS_STRINGS_PREFIX_FUNCTION_NAIVE_INCLUDED
