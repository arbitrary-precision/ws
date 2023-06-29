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
# libgmp
#
set(GMP_PREFIX "${CMAKE_BINARY_DIR}")
set(GMP_SOURCE_DIR "${GMP_PREFIX}/gmp/src")
set(GMP_BINARY_DIR "${GMP_PREFIX}/gmp/bin")
set(GMP_INSTALL_DIR "${GMP_PREFIX}")
set(GMP_C_FLAGS "-std=c${CMAKE_C_STANDARD} ${CMAKE_C_FLAGS}")
set(GMP_CXX_FLAGS "-std=c++${CMAKE_CXX_STANDARD} ${CMAKE_CXX_FLAGS}")
set(GMP_DOWNLOAD_COMMAND cp -RaT ${CMAKE_SOURCE_DIR}/src/gmp ${GMP_SOURCE_DIR})
set(GMP_CONFIGURE_COMMAND true
    && cd ${GMP_BINARY_DIR}
    && ${GMP_SOURCE_DIR}/configure
    --prefix=${GMP_INSTALL_DIR}
    --disable-shared
    --enable-cxx
    ABI=64
    CC=${CMAKE_C_COMPILER}
    CFLAGS=${GMP_C_FLAGS}
    CXX=${CMAKE_CXX_COMPILER}
    CXXFLAGS=${GMP_CXX_FLAGS}
)
set(GMP_BUILD_COMMAND make)
set(GMP_INSTALL_COMMAND make install)

# Target for building.
include(ExternalProject)
ExternalProject_Add(
    gmp
    PREFIX ${GMP_PREFIX}
    SOURCE_DIR ${GMP_SOURCE_DIR}
    BINARY_DIR ${GMP_BINARY_DIR}
    INSTALL_DIR ${GMP_INSTALL_DIR}
    DOWNLOAD_COMMAND ${GMP_DOWNLOAD_COMMAND}
    CONFIGURE_COMMAND ${GMP_CONFIGURE_COMMAND}
    BUILD_COMMAND ${GMP_BUILD_COMMAND}
    INSTALL_COMMAND ${GMP_INSTALL_COMMAND}
)

# Target for linking.
add_library(libgmp INTERFACE)

add_dependencies(libgmp gmp)

target_link_libraries(libgmp INTERFACE
    "${GMP_INSTALL_DIR}/lib/libgmpxx.a"
    "${GMP_INSTALL_DIR}/lib/libgmp.a"
)

target_include_directories(libgmp INTERFACE
    "${GMP_INSTALL_DIR}/include"
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
