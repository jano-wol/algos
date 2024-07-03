set(target applications-data_structures-range_minimum_queries-tests)

set(sources
   TestRangeMinimumQueries.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

