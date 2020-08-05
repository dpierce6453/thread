cmake_minimum_required(VERSION 3.16)
project(thread)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

set(Libsources
        Exercise1/thread1.cpp
	LinesList.cpp
        Exercise1/cmd_clean.cpp
        Exercise1/cmd_engine.cpp
)

set(Libheaders
        Exercise1/thread1.h
	LinesList.h
        Exercise1/cmd_clean.h
        Exercise1/cmd_engine.h
	SafeQueue.h
		Exercise2/commandData.cpp Exercise2/commandData.h Exercise2/queueThread.cpp Exercise2/queueThread.h Exercise2/QueueThreadCannotStart.cpp Exercise2/QueueThreadCannotStart.h Exercise2/workerThread.cpp Exercise2/workerThread.h)

add_library(Mylib STATIC ${Libsources} ${Libheaders})

add_executable(thread main.cpp Exercise1/thread1.cpp Exercise1/thread1.h LinesList.cpp LinesList.h Exercise1/cmd_clean.cpp Exercise1/cmd_clean.h Exercise1/command.h Exercise1/cmd_engine.cpp Exercise1/cmd_engine.h SafeQueue.h Exercise1/Exercise1Main.cpp)

add_subdirectory(tests)