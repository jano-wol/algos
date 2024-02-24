set(target applications-strings-longest-pallindrome-tests)

set(sources
   TestLongestPallindrome.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

