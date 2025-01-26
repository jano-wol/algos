set(target algos-data_structures-link_cut_tree-tests)

set(sources
    TestLinkCutTree.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

