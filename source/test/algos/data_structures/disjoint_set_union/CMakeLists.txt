set(target algos-data_structures-disjoint_set_union-tests)

set(sources
    TestDisjointSetUnion.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

