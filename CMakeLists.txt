cmake_minimum_required(VERSION 3.15)
project(SO2_1 C CXX)

set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)

find_package(Threads)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(main main.cpp ${SRC_FILES})

target_link_libraries(main ${CURSES_LIBRARIES})

target_include_directories(main PUBLIC ${PROJECT_SOURCE_DIR}/header)