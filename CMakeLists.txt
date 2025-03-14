cmake_minimum_required(VERSION 3.28)
project(stack_duplicate_fifo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest)
if (NOT ${GTest_FOUND})
    include(gtest/gtest.cmake)
endif()

enable_testing()
add_executable(stack_duplicate_fifo_test
        stack_duplicate_fifo.h test.cpp)
target_link_libraries(stack_duplicate_fifo_test
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(stack_duplicate_fifo_test)

add_executable(stack_duplicate_fifo
        stack_duplicate_fifo.h main.cpp)