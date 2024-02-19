set(target algos-data-structures-tests)

set(sources
    TestDisjointSetUnion.cpp
    TestMinimumQueue.cpp
    TestMinimumStack.cpp
    TestSparseTable.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

