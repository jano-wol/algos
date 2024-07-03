set(target algos-data_structures-sparse_table-tests)

set(sources
    TestSparseTable.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

