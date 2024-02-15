#include <gmock/gmock.h>

#include <cstring>

#include "./../../../applications/strings/count_substring_occurance/count_substring_occurance.h"

TEST(CountSubstringOccurance, TestCountSubstringOccurance)
{
  std::string str = "ab";
  std::string text = "aaaabababababababbbbbabbbb";
  std::cout << countSubstringOccuranceNaive(str, text) << "\n";
  std::cout << countSubstringOccurance(str, text) << "\n";
}