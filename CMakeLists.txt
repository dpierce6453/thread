cmake_minimum_required(VERSION 3.16)
project(thread)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

set(Libsources
	thread1.cpp
	LinesList.cpp
)

set(Libheaders
    thread1.h
	LinesList.h
)

add_library(Mylib STATIC ${Libsources} ${Libheaders})

add_executable(thread main.cpp thread1.cpp thread1.h LinesList.cpp LinesList.h)

add_subdirectory(tests)