set(target algos-strings-prefix_function-tests)

set(sources
    TestPrefixFunction.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

