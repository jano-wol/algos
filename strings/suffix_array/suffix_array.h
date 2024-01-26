#ifndef ALGOS_STRINGS_SUFFIX_ARRAY_INCLUDED
#define ALGOS_STRINGS_SUFFIX_ARRAY_INCLUDED

#include <iostream>
#include <string>
#include <vector>

class SuffixArray
{
public:
  static std::vector<int> suffixArray(const std::string& str)
  {
    std::vector<uint8_t> input(str.begin(), str.end());

    checkInput(input);

    return {};
  }

private:
  static void checkInput(const std::vector<uint8_t>& input, std::string context = "SuffixArray")
  {
    for (auto i : input) {
      if (i == 0) {
        std::cerr << "input has zero character! context=" << context << "\n";
      }
    }
  }
};
#endif  // ALGOS_STRINGS_SUFFIX_ARRAY_INCLUDED
