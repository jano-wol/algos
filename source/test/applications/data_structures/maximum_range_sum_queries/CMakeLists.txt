set(target applications-data_structures-maximum_range_sum_queries-tests)

set(sources
   TestMaximumRangeSumQueries.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

