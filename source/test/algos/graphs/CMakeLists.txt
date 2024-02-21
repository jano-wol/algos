set(target algos-graphs-tests)

set(sources
    TestBFS.cpp
    TestKruskal.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

