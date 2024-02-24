set(target algos-strings-suffix_array-tests)

set(sources
    TestSuffixArray.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

