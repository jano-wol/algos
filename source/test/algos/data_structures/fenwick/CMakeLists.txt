﻿set(target algos-data_structures-fenwick-tests)

set(sources
    TestFenwick.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

