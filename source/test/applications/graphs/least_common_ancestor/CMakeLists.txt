﻿set(target applications-graphs-least_common_ancestor-tests)

set(sources
   TestLeastCommonAncestor.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

