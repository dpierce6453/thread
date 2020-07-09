cmake_minimum_required(VERSION 3.8)

set(This MyTests)
set(GTEST_DIR C:/Users/harldanp.CITRITE/source/repos/googletest)
set(GTEST_LIB_DIR ${GTEST_DIR}/build/lib)

set(Headers
)

set(Sources
	MyTests.cpp
	LineListTests.cpp)

add_executable(${This} ${Sources} ${Headers})

target_include_directories(${This} SYSTEM PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>
    ${GTEST_DIR}/googletest/include
)


target_link_libraries(${This}  PUBLIC
	${GTEST_LIB_DIR}/libgmock.a
	${GTEST_LIB_DIR}/libgtest.a
	${GTEST_LIB_DIR}/libgtest_main.a
	Mylib
)

add_test(
	NAME ${This}
	COMMAND ${This}
)