set(target applications-strings-longest-common-substring-tests)

set(sources
   TestLongestCommonSubstring.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

