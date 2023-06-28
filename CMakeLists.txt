# SPDX-FileCopyrightText: (c) 2023 Volodymyr Zakalyk <volodymyr.zakalyk@gmail.com>
# SPDX-License-Identifier: MIT

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
# ap.
#
set(INCLUDE_DIRS_AP
    "${CMAKE_SOURCE_DIR}/src/ap"
)

#
# bmp.
#
set(INCLUDE_DIRS_BMP
    "${CMAKE_SOURCE_DIR}/src/bmp/include"
    "${CMAKE_SOURCE_DIR}/src/bmp/include/boost/multiprecision"
)

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

set(INCLUDE_DIRS_GTEST
    "${CMAKE_SOURCE_DIR}/src/gtest/googletest/include"
    "${CMAKE_SOURCE_DIR}/src/gtest/googletest/include/gtest"
)

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
