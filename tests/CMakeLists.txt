cmake_minimum_required(VERSION 3.8)

set(This MyTests)
set(GTEST_DIR C:/Users/Dan/source/repos/googletest)
set(GTEST_LIB_DIR ${GTEST_DIR}/build/lib)

set(Headers
)

set(Sources
	MyTests.cpp
	LineListTests.cpp SafeQueueTests.cpp testThread.cpp testThread.h queueThreadTests.cpp)

add_executable(${This} ${Sources} ${Headers})

target_include_directories(${This} SYSTEM PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    ${GTEST_DIR}/googletest/include
)

target_link_directories(${This} PUBLIC ${GTEST_LIB_DIR})

target_link_libraries(${This} PUBLIC gmock gtest gtest_main	Mylib )

add_test(
	NAME ${This}
	COMMAND ${This}
)