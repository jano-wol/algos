set(target applications-data_structures-range_sum_queries-tests)

set(sources
   TestRangeSumQueries.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

