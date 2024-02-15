#ifndef ALGOS_STRINGS_STRING_HASH_INCLUDED
#define ALGOS_STRINGS_STRING_HASH_INCLUDED

#include <string>

class StringHash
{
public:
  static long long stringHash(std::string const& s, long long p = 263, long long m = 1e9 + 9)
  {
    long long hashValue = 0;
    long long pow = 1;
    for (char c : s) {
      hashValue = (hashValue + (static_cast<int>(c) + 1) * pow) % m;
      pow = (pow * p) % m;
    }
    return hashValue;
  }
};

#endif  // ALGOS_STRINGS_STRING_HASH_INCLUDED
