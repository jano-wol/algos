set(target applications-strings-calc_different_substrings-tests)

set(sources
   TestCalcDifferentSubstrings.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

