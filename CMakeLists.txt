cmake_minimum_required(VERSION 3.22)

#
# Project.
#
set(CMAKE_C_STANDARD 17 CACHE STRING "C standard")
set(CMAKE_C_COMPILER clang CACHE STRING "C compiler")
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "C++ standard")
set(CMAKE_CXX_COMPILER clang++ CACHE STRING "C++ compiler")
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(ap C CXX)

#
# gtest.
#
include(FetchContent)
FetchContent_Declare(
    gtest
    URL "${CMAKE_SOURCE_DIR}/src/gtest"
)

# For Windows: Prevent overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(gtest)

#
# test.
#
set(TEST_SRC_DIR "${CMAKE_SOURCE_DIR}/src/test")

add_executable(test
    "${TEST_SRC_DIR}/test.cpp"
)

target_link_libraries(test
    GTest::gtest_main
)
