set(target applications-data-structures-closest-in-range-queries-tests)

set(sources
   TestClosestInRangeQueries.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

