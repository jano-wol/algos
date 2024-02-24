set(target algos-data-structures-minimum_stack-tests)

set(sources
    TestMinimumStack.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

