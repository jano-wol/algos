set(target algos-data_structures-sqrt_tree-tests)

set(sources
    TestSqrtTree.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

