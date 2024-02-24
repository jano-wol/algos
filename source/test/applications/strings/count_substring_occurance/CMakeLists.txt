set(target applications-strings-count-substring-occurance-tests)

set(sources
   TestCountSubstringOccurance.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

