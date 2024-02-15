#include <gmock/gmock.h>

#include "./../../../algos/strings/string_hash/string_hash.h"

namespace
{
void testExpected(const std::string& str, size_t expected)
{
  const auto& [hash, params] = StringHash::stringHash(str);
  const auto& [p, m] = params;
  EXPECT_EQ(hash, expected);
  EXPECT_EQ(p, 263);
  EXPECT_EQ(m, 1e9 + 9);
}

void testExpected(const std::string& str, size_t expected, uint64_t p, uint64_t m)
{
  const auto& [hash, params] = StringHash::stringHash(str, p, m);
  const auto& [p1, m1] = params;
  EXPECT_EQ(hash, expected);
  EXPECT_EQ(p, p1);
  EXPECT_EQ(m, m1);
}

void testPrefix(const std::string& str)
{
  std::vector<uint64_t> hashes;
  for (size_t i = 0; i <= str.size(); ++i) {
    auto curr = str.substr(0, i);
    const auto& [hash, params] = StringHash::stringHash(curr);
    hashes.push_back(hash);
  }
  auto prefixHashes = StringHash::prefixHashes(str);
  const auto& [p, m] = prefixHashes.second;
  EXPECT_EQ(hashes, prefixHashes.first);
  EXPECT_EQ(p, 263);
  EXPECT_EQ(m, 1e9 + 9);
}

void testPrefix(const std::string& str, uint64_t p, uint64_t m)
{
  std::vector<uint64_t> hashes;
  for (size_t i = 0; i <= str.size(); ++i) {
    auto curr = str.substr(0, i);
    const auto& [hash, params] = StringHash::stringHash(curr, p, m);
    hashes.push_back(hash);
  }
  auto prefixHashes = StringHash::prefixHashes(str, p, m);
  const auto& [p1, m1] = prefixHashes.second;
  EXPECT_EQ(hashes, prefixHashes.first);
  EXPECT_EQ(p, p1);
  EXPECT_EQ(m, m1);
}
}  // namespace

TEST(StringHash, TestStringHash)
{
  testExpected("", 0);
  testExpected("", 0, 7, 71);
  testExpected(" ", 33);
  testExpected(" ", 33, 7, 71);
  testExpected("a", 98);
  testExpected("a", 27, 7, 71);
  testExpected("banana", 703622327);
  testExpected("banana", 703622327, 263, 1e9 + 9);
  testExpected("bbbaaabababbabbbaaaaabbbbbb_jGjjHG85_???##??###_843", 598108708);
  testExpected("bbbaaabababbabbbaaaaabbbbbb_jGjjHG85_???##??###_843", 51, 7, 71);
}

TEST(StringHash, TestPrefixHashes)
{
  testPrefix("");
  testPrefix("", 7, 71);
  testPrefix(" ");
  testPrefix(" ", 7, 71);
  testPrefix("a");
  testPrefix("a", 7, 71);
  testPrefix("banana");
  testPrefix("banana", 263, 1e9 + 9);
  testPrefix("bbbaaabababbabbbaaaaabbbbbb_jGjjHG85_???##??###_843");
  testPrefix("bbbaaabababbabbbaaaaabbbbbb_jGjjHG85_???##??###_843", 7, 71);
}
