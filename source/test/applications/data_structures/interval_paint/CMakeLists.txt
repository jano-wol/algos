﻿set(target applications-data_structures-interval_paint-tests)

set(sources
   TestIntervalPaint.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

