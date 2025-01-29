cmake_minimum_required(VERSION 3.30)

project(Tasks)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

enable_testing()

add_subdirectory(googletest)
add_subdirectory(tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_library(Tasks main.cpp
        Task1/Task1.h
        Task1/Task1.cpp
        Task2/Task2.h
        Task2/Task2.cpp
        Task3/Task3.cpp
        Task3/Task3.h)

add_executable(TasksExecutable main.cpp)
target_link_libraries(TasksExecutable PRIVATE Tasks)