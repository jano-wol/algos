set(target applications-strings-prefix_freq-tests)

set(sources
   TestPrefixFreq.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

