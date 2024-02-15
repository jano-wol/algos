#ifndef APPLICATIONS_STRINGS_LONGEST_PALLINDROME_INCLUDED
#define APPLICATIONS_STRINGS_LONGEST_PALLINDROME_INCLUDED

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include "./../../../algos/strings/string_hash/string_hash.h"

namespace
{
uint64_t calcSubstringDelatedHash(size_t i, size_t j, const std::vector<uint64_t>& hashes, uint64_t m,
                                  const std::vector<uint64_t>& p_pow)
{
  size_t n = hashes.size() - 1;
  uint64_t hash = (hashes[j] + m - hashes[i]) % m;
  hash = (hash * p_pow[n - i - 1]) % m;
  return hash;
}

bool isPallindrome(std::pair<size_t, size_t> interval, const std::vector<uint64_t>& hashes,
                   const std::vector<uint64_t>& hashesReverse, uint64_t m, const std::vector<uint64_t>& p_pow, size_t n)
{
  const auto& [i, j] = interval;
  uint64_t hash = calcSubstringDelatedHash(i, j, hashes, m, p_pow);
  uint64_t hashReverse = calcSubstringDelatedHash(n - j, n - i, hashesReverse, m, p_pow);
  return (hash == hashReverse);
}

std::optional<std::pair<size_t, size_t>> existsPallindromeWithSize(size_t size, const std::vector<uint64_t>& hashes,
                                                                   const std::vector<uint64_t>& hashesReverse,
                                                                   uint64_t m, const std::vector<uint64_t>& p_pow,
                                                                   size_t n)
{
  if (n < size) {
    return std::nullopt;
  }
  for (size_t i = 0; i <= n - size; ++i) {
    if (isPallindrome({i, i + size}, hashes, hashesReverse, m, p_pow, n)) {
      return std::pair<size_t, size_t>{i, i + size};
    }
  }
  return std::nullopt;
}

void binarySearch(size_t l, size_t r, const std::vector<uint64_t>& hashes, const std::vector<uint64_t>& hashesReverse,
                  uint64_t m, const std::vector<uint64_t>& p_pow, size_t n, std::pair<size_t, size_t>& ret)
{
  if (l > r) {
    return;
  }

  size_t mid1 = (l + r) / 2;
  size_t mid2 = mid1 + 1;

  auto ret1 = existsPallindromeWithSize(mid1, hashes, hashesReverse, m, p_pow, n);
  auto ret2 = existsPallindromeWithSize(mid2, hashes, hashesReverse, m, p_pow, n);
  size_t newL = l;
  size_t newR = r;
  if (ret1) {
    ret = *ret1;
    newL = mid1 + 1;
  }
  if (ret2) {
    ret = *ret2;
    newL = mid2 + 1;
  }
  if ((!ret1) && (!ret2)) {
    newR = mid1 - 1;
  }
  binarySearch(newL, newR, hashes, hashesReverse, m, p_pow, n, ret);
}
}  // namespace

std::pair<size_t, size_t> longestPallindromeNaive(const std::string& str)
{
  if (str.empty()) {
    return {0, 0};
  }
  auto n = str.size();
  size_t longestPallindromeLength = 1;
  std::pair<size_t, size_t> longestPallindromeInterval = {0, 1};
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = i + longestPallindromeLength + 1; j <= n; ++j) {
      size_t currLength = j - i;
      auto curr = str.substr(i, currLength);
      bool isPallindrome = true;
      for (size_t k = 0; k <= currLength / 2; ++k) {
        if (curr[k] != curr[currLength - 1 - k]) {
          isPallindrome = false;
          break;
        }
      }
      if (isPallindrome) {
        longestPallindromeLength = j - i;
        longestPallindromeInterval = {i, j};
      }
    }
  }
  return longestPallindromeInterval;
}

// Stochastic algorithm. runtime = O(n log(n)), memory = O(n), where n = |str|.
std::pair<size_t, size_t> longestPallindromeHash(const std::string& str)
{
  if (str.empty()) {
    return {0, 0};
  }
  size_t n = str.size();
  std::string strReverse(str);
  std::reverse(strReverse.begin(), strReverse.end());

  const auto& [hashes, hashParams] = StringHash::prefixHashes(str);
  const auto& [hashesReverse, hashParamsReverse] = StringHash::prefixHashes(strReverse);
  const auto& [p, m] = hashParams;
  std::vector<uint64_t> p_pow(n + 1);
  p_pow[0] = 1;
  for (size_t i = 1; i < n; i++) {
    p_pow[i] = (p_pow[i - 1] * p) % m;
  }

  std::pair<size_t, size_t> ret = {0, 1};
  binarySearch(2, n, hashes, hashesReverse, m, p_pow, n, ret);
  return ret;
}
#endif  // APPLICATIONS_STRINGS_LONGEST_PALLINDROME_INCLUDED
