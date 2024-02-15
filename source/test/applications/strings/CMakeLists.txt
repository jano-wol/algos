set(target applications-strings-tests)

set(sources
   TestCalcDifferentSubstrings.cpp
   TestCompress.cpp
   TestCountSubstringOccurance.cpp
   TestLongestPallindrome.cpp
   TestPrefixFreq.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

