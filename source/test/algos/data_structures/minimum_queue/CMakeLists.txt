set(target algos-data_structures-minimum_queue-tests)

set(sources
    TestMinimumQueue.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

