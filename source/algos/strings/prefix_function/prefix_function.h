#ifndef ALGOS_STRINGS_PREFIX_FUNCTION_INCLUDED
#define ALGOS_STRINGS_PREFIX_FUNCTION_INCLUDED

#include <string>
#include <vector>

class PrefixFunction
{
public:
  // runtime = O(n), memory = O(n), where n = |str|.
  template <typename T>
  static std::vector<size_t> prefixFunction(const T& str)
  {
    size_t n = str.size();
    std::vector<size_t> pi(n);
    for (size_t i = 1; i < n; i++) {
      size_t j = pi[i - 1];
      while (j > 0 && str[i] != str[j]) {
        j = pi[j - 1];
      }
      if (str[i] == str[j]) {
        j++;
      }
      pi[i] = j;
    }
    return pi;
  }
};

#endif  // ALGOS_STRINGS_PREFIX_FUNCTION_INCLUDED
