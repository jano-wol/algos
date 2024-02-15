#ifndef APPLICATIONS_STRINGS_COMPRESS_INCLUDED
#define APPLICATIONS_STRINGS_COMPRESS_INCLUDED

#include <algorithm>
#include <string>
#include <vector>

#include "./../../../algos/strings/prefix_function/prefix_function.h"
#include "./../../../algos/strings/z_function/z_function.h"

size_t compressNaive(const std::string& str)
{
  if (str.empty()) {
    return 0;
  }
  auto n = str.size();
  for (size_t i = 1; i <= n; ++i) {
    if (n % i != 0) {
      continue;
    }
    auto curr = str.substr(0, i);
    bool compressSuccess = true;
    for (size_t j = 0; j < n / i; ++j) {
      auto curr2 = str.substr(j * i, i);
      if (curr != curr2) {
        compressSuccess = false;
        break;
      }
    }
    if (compressSuccess) {
      return i;
    }
  }
  return 0;
}

// runtime = O(n), memory = O(n), where n = |str|.
size_t compressZFunction(const std::string& str)
{
  if (str.empty()) {
    return 0;
  }
  auto n = str.size();
  auto z = ZFunction::zFunction(str);
  for (size_t i = 1; i < n; ++i) {
    if (n % i != 0) {
      continue;
    }
    if (i + z[i] == n) {
      return i;
    }
  }
  return n;
}

// runtime = O(n), memory = O(n), where n = |str|.
size_t compressPrefixFunction(const std::string& str)
{
  if (str.empty()) {
    return 0;
  }
  auto n = str.size();
  auto pi = PrefixFunction::prefixFunction(str);
  auto candidate = n - pi.back();
  return ((n % candidate) == 0) ? candidate : n;
}

#endif  // APPLICATIONS_STRINGS_COMPRESS_INCLUDED
