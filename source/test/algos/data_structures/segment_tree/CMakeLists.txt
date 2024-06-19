set(target algos-data-structures-segment-tree-tests)

set(sources
    TestSegmentTree.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

