set(target applications-data-structures-range-mode-queries-tests)

set(sources
   TestRangeModeQueries.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

