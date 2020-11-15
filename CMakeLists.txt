cmake_minimum_required(VERSION 3.16)

set(This thread)
set(Thislib thread_lib)

project(${This})
project(${Thislib})

set(CMAKE_CXX_STANDARD 14)

set(DAN_LOCAL_DIR C:/Users/Dan/source/repos)

set(GTEST_DIR ${DAN_LOCAL_DIR}/googletest)
set(Protobuf_INCLUDE_DIR ${DAN_LOCAL_DIR}/googleprotocolbuffers/protobuf-3.12.3/src)
set(Protobuf_LIBRARIES ${DAN_LOCAL_DIR}/googleprotocolbuffers/protobuf-3.12.3/cmake/build)

set(GPC_PROJECT ${DAN_LOCAL_DIR}/gpc/cmake-build-debug/gpcinterfaces)

enable_testing()

set(Libsources
	LinesList.cpp
    Exercise1/thread1.cpp
    Exercise1/cmd_clean.cpp
    Exercise1/cmd_engine.cpp
	Exercise2/workerThread.cpp
	Exercise2/queueThread.cpp
	Exercise2/QueueThreadCannotStart.cpp
)

set(Libheaders
	LinesList.h
	SafeQueue.h
	Exercise1/thread1.h
    Exercise1/cmd_clean.h
    Exercise1/cmd_engine.h
	Exercise2/workerThread.h
	Exercise2/queueThread.h
	Exercise2/QueueThreadCannotStart.h
    )

set(Mainsources
	Exercise1/thread1.cpp
	Exercise1/thread1.h
	Exercise1/cmd_clean.cpp
	Exercise1/cmd_clean.h
	Exercise1/command.h
	Exercise1/cmd_engine.cpp
	Exercise1/cmd_engine.h
	Exercise1/Exercise1Main.cpp
	Exercise2/Exercise2Main.cpp
	Exercise2/queueThread.h
	Exercise2/queueThread.cpp
	Exercise2/workerThread.h
	Exercise2/workerThread.cpp
	LinesList.cpp
	LinesList.h
	SafeQueue.h
)


add_library(${Thislib} STATIC ${Libsources} ${Libheaders})

target_include_directories(${Thislib} PUBLIC ${Protobuf_INCLUDE_DIR} ${GPC_PROJECT})

target_link_directories(${Thislib} PUBLIC ${GPC_PROJECT} ${Protobuf_LIBRARIES})

target_link_libraries(${Thislib}
	PUBLIC gpcinterfaces
    PRIVATE protobuf
)


add_executable(${This} main.cpp ${Mainsources})
target_include_directories(${This} PUBLIC ${Protobuf_INCLUDE_DIR} ${GPC_PROJECT})
target_link_directories(${This} PUBLIC ${GPC_PROJECT} ${Protobuf_LIBRARIES})
target_link_libraries(${This}
	PUBLIC gpcinterfaces
    PRIVATE protobuf
)

add_subdirectory(tests)