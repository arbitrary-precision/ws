cmake_minimum_required(VERSION 3.22)

# Check required variables before defining the project.
list(APPEND REQUIRED_VARIABLES
    "CMAKE_C_FLAGS"
    "CMAKE_C_COMPILER"
    "CMAKE_C_STANDARD"
    "CMAKE_CXX_FLAGS"
    "CMAKE_CXX_COMPILER"
    "CMAKE_CXX_STANDARD"
)

foreach(VARIABLE ${REQUIRED_VARIABLES})
    if("${${VARIABLE}}" STREQUAL "")
        message(SEND_ERROR "Variable is not set: ${VARIABLE}")
    endif()
endforeach()

# Define project.
project(ap)

# Set other variables.
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# gtest
include(FetchContent)
FetchContent_Declare(
    gtest
    URL ${CMAKE_SOURCE_DIR}/src/gtest
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

# test
set(TEST_SRC_DIR "${CMAKE_SOURCE_DIR}/src/test")

add_executable(test
    "${TEST_SRC_DIR}/test.cpp"
)

target_link_libraries(test
    GTest::gtest_main
)
