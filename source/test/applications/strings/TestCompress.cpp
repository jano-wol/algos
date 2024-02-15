#include <gmock/gmock.h>

#include <cstring>

#include "./../../../applications/strings/compress/compress.h"

TEST(Compress, TestCompress)
{
  std::string str = "aabaaabaaaba";
  std::cout << compressNaive(str) << "\n";
  std::cout << compressZFunction(str) << "\n";
  std::cout << compressPrefixFunction(str) << "\n";
}