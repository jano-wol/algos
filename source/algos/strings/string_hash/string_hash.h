#ifndef ALGOS_STRINGS_STRING_HASH_INCLUDED
#define ALGOS_STRINGS_STRING_HASH_INCLUDED

#include <string>
#include <vector>

class StringHash
{
public:
  static std::pair<uint64_t, std::pair<std::vector<uint64_t>, uint64_t>> stringHash(std::string const& s,
                                                                                    uint64_t p = 263,
                                                                                    uint64_t m = 1e9 + 9)
  {
    uint64_t hashValue = 0;
    std::vector<uint64_t> pPow;
    pPow.reserve(s.size() + 2);
    pPow.push_back(1);
    uint64_t pow = 1;
    for (char c : s) {
      hashValue = (hashValue + (static_cast<int>(c) + 1) * pow) % m;
      pow = (pow * p) % m;
      pPow.push_back(pow);
    }
    if (pPow.size() == 1) {
      pPow.push_back(p);
    }
    return {hashValue, {pPow, m}};
  }

  static std::pair<std::vector<uint64_t>, std::pair<std::vector<uint64_t>, uint64_t>> prefixHashes(std::string const& s,
                                                                                                   uint64_t p = 263,
                                                                                                   uint64_t m = 1e9 + 9)
  {
    uint64_t pow = 1;
    std::vector<uint64_t> ret;
    std::vector<uint64_t> pPow;
    ret.reserve(s.size() + 1);
    ret.push_back(0);
    pPow.reserve(s.size() + 2);
    pPow.push_back(1);
    uint64_t hashValue = 0;
    for (char c : s) {
      hashValue = (hashValue + (static_cast<int>(c) + 1) * pow) % m;
      pow = (pow * p) % m;
      ret.push_back(hashValue);
      pPow.push_back(pow);
    }
    if (pPow.size() == 1) {
      pPow.push_back(p);
    }
    return {ret, {pPow, m}};
  }

  static uint64_t calcSubstringDelatedHash(size_t i, size_t j, const std::vector<uint64_t>& hashes,
                                           const std::vector<uint64_t>& pPow, uint64_t m)
  {
    if (hashes.empty()) {
      throw std::invalid_argument("prefix hashes cannot be empty");
    }
    size_t n = hashes.size() - 1;
    if (n <= i) {
      throw std::invalid_argument("substring left end is too large");
    }
    if (n < j) {
      throw std::invalid_argument("substring right end is too large");
    }
    uint64_t hash = (hashes[j] + m - hashes[i]) % m;
    hash = (hash * pPow[n - i - 1]) % m;
    return hash;
  }
};

#endif  // ALGOS_STRINGS_STRING_HASH_INCLUDED
