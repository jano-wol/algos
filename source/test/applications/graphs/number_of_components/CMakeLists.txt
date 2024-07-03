set(target applications-graphs-number_of_components-tests)

set(sources
   TestNumberOfComponents.cpp
)

add_executable(${target} ${sources})

target_link_libraries(${target}
	PRIVATE
	gmock-dev
	GTest::gtest_main
)

gtest_discover_tests(${target})

