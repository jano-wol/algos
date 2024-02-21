set(target applications-data-structures-tests)

set(sources
   TestIntervalPaint.cpp
   TestRangeMinimumQueries.cpp
   TestSlidingMinimum.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

