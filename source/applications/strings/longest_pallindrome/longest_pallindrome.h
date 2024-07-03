#ifndef APPLICATIONS_STRINGS_LONGEST_PALLINDROME_INCLUDED
#define APPLICATIONS_STRINGS_LONGEST_PALLINDROME_INCLUDED

#include <algorithm>
#include <optional>
#include <string>
#include <vector>

#include "./../../../algos/strings/manacher/manacher.h"
#include "./../../../algos/strings/string_hash/string_hash.h"

namespace algos::longestpallindrome_utils
{
bool isPallindrome(std::pair<size_t, size_t> interval, const std::vector<uint64_t>& hashes,
                   const std::vector<uint64_t>& hashesReverse, const std::vector<uint64_t>& pPow, uint64_t m, size_t n)
{
  const auto& [i, j] = interval;
  uint64_t hash = StringHash::calcSubstringDelatedHash(i, j, hashes, pPow, m);
  uint64_t hashReverse = StringHash::calcSubstringDelatedHash(n - j, n - i, hashesReverse, pPow, m);
  return (hash == hashReverse);
}

std::optional<std::pair<size_t, size_t>> existsPallindromeWithSize(size_t size, const std::vector<uint64_t>& hashes,
                                                                   const std::vector<uint64_t>& hashesReverse,
                                                                   const std::vector<uint64_t>& pPow, uint64_t m,
                                                                   size_t n)
{
  if (n < size) {
    return std::nullopt;
  }
  for (size_t i = 0; i <= n - size; ++i) {
    if (isPallindrome({i, i + size}, hashes, hashesReverse, pPow, m, n)) {
      return std::pair<size_t, size_t>{i, i + size};
    }
  }
  return std::nullopt;
}

void binarySearch(size_t l, size_t r, const std::vector<uint64_t>& hashes, const std::vector<uint64_t>& hashesReverse,
                  uint64_t m, const std::vector<uint64_t>& pPow, size_t n, std::pair<size_t, size_t>& ret)
{
  if (l > r) {
    return;
  }

  size_t mid1 = (l + r) / 2;
  size_t mid2 = mid1 + 1;

  auto ret1 = existsPallindromeWithSize(mid1, hashes, hashesReverse, pPow, m, n);
  auto ret2 = existsPallindromeWithSize(mid2, hashes, hashesReverse, pPow, m, n);
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
  binarySearch(newL, newR, hashes, hashesReverse, m, pPow, n, ret);
}
}  // namespace algos::longestpallindrome_utils

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

// Stochastic algorithm. runtime = O(n * log(n)), memory = O(n), where n = |str|.
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
  const auto& [pPow, m] = hashParams;
  std::pair<size_t, size_t> ret = {0, 1};
  algos::longestpallindrome_utils::binarySearch(2, n, hashes, hashesReverse, m, pPow, n, ret);
  return ret;
}

// runtime = O(n), memory = O(n), where n = |str|.
std::pair<size_t, size_t> longestPallindromeManacher(const std::string& str)
{
  if (str.empty()) {
    return {0, 0};
  }
  const auto& [odd, even] = Manacher::manacher(str);
  auto itOdd = std::max_element(odd.begin(), odd.end());
  auto itEven = std::max_element(even.begin(), even.end());
  size_t oddMax = *itOdd;
  size_t evenMax = *itEven;
  if ((2 * oddMax - 1) > (2 * evenMax)) {
    size_t oddIdx = std::distance(odd.begin(), itOdd);
    return {(oddIdx + 1) - oddMax, oddIdx + oddMax};
  } else {
    size_t evenIdx = std::distance(even.begin(), itEven);
    return {evenIdx - evenMax, evenIdx + evenMax};
  }
  return {};
}
#endif  // APPLICATIONS_STRINGS_LONGEST_PALLINDROME_INCLUDED
