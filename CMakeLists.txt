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