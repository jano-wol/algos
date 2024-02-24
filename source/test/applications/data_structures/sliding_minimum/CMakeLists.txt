set(target applications-data-structures-sliding-minimum-tests)

set(sources
   TestSlidingMinimum.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

