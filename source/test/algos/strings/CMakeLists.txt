set(target algos-strings-tests)

set(sources
    TestKasai.cpp
    TestManacher.cpp
    TestPrefixFunction.cpp
    TestStringHash.cpp
    TestSuffixArray.cpp
    TestSuffixAutomaton.cpp
    TestZFunction.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

