cmake_minimum_required(VERSION 3.30)

add_executable(Tests test.cpp)
target_link_libraries(Tests PUBLIC gtest gtest_main gmock Tasks)

add_test(NAME RunTests COMMAND Tests)