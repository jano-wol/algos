set(target algos-data-structures-sqrt_decomposition-tests)

set(sources
    TestSqrtDecomposition.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

