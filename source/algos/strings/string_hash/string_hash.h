#ifndef ALGOS_STRINGS_STRING_HASH_INCLUDED
#define ALGOS_STRINGS_STRING_HASH_INCLUDED

#include <string>
#include <vector>

class StringHash
{
public:
  static std::pair<uint64_t, std::pair<uint64_t, uint64_t>> stringHash(std::string const& s, uint64_t p = 263,
                                                                       uint64_t m = 1e9 + 9)
  {
    uint64_t hashValue = 0;
    uint64_t pow = 1;
    for (char c : s) {
      hashValue = (hashValue + (static_cast<int>(c) + 1) * pow) % m;
      pow = (pow * p) % m;
    }
    return {hashValue, {p, m}};
  }

  static std::pair<std::vector<uint64_t>, std::pair<uint64_t, uint64_t>> prefixHashes(std::string const& s,
                                                                                      uint64_t p = 263,
                                                                                      uint64_t m = 1e9 + 9)
  {
    uint64_t pow = 1;
    std::vector<uint64_t> ret;
    ret.reserve(s.size() + 1);
    ret.push_back(0);
    uint64_t hashValue = 0;
    for (char c : s) {
      hashValue = (hashValue + (static_cast<int>(c) + 1) * pow) % m;
      pow = (pow * p) % m;
      ret.push_back(hashValue);
    }
    return {ret, {p, m}};
  }
};

#endif  // ALGOS_STRINGS_STRING_HASH_INCLUDED
