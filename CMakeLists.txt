# SPDX-FileCopyrightText: (c) 2023 Volodymyr Zakalyk <volodymyr.zakalyk@gmail.com>
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.22)

#
# AP - general configuration
#
set(CMAKE_C_STANDARD 17 CACHE STRING "C standard")
set(CMAKE_C_COMPILER clang CACHE STRING "C compiler")
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 14 CACHE STRING "C++ standard")
set(CMAKE_CXX_COMPILER clang++ CACHE STRING "C++ compiler")
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(AP C CXX)

#
# libap
#
add_library(libap INTERFACE)

target_include_directories(libap INTERFACE
    "${CMAKE_SOURCE_DIR}/src/ap"
)

#
# libbmp
#
add_library(libbmp INTERFACE)

target_include_directories(libbmp INTERFACE
    "${CMAKE_SOURCE_DIR}/src/bmp/include"
    "${CMAKE_SOURCE_DIR}/src/bmp/include/boost/multiprecision"
)

#
# libgtest
#
include(FetchContent)
FetchContent_Declare(
    gtest
    URL "${CMAKE_SOURCE_DIR}/src/gtest"
)

# For Windows: Prevent overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(gtest)

add_library(libgtest INTERFACE)

target_link_libraries(libgtest INTERFACE
    GTest::gtest_main
)

target_include_directories(libgtest INTERFACE
    "${CMAKE_SOURCE_DIR}/src/gtest/googletest/include"
    "${CMAKE_SOURCE_DIR}/src/gtest/googletest/include/gtest"
)

#
# test
#
set(TEST_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src/test")

add_executable(test
    "${TEST_SOURCE_DIR}/test.cpp"
)

target_link_libraries(test PRIVATE
    libgtest
    libbmp
    libap
)
