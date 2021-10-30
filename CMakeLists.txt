cmake_minimum_required(VERSION 2.9)

project(ap_workspace)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Release)

# Include everything in dependencies
set(ROOT_DIR ${CMAKE_CURRENT_BINARY_DIR}/..)
set(ROOT_SRC_DIR ${ROOT_DIR}/src)
set(ROOT_BUILD_DIR ${ROOT_DIR}/build)

#
# Google Test dependency
#

# Path to Google Test directories
set(GTEST_DIR ${ROOT_SRC_DIR}/gtest)
set(GTEST_DL_DIR ${GTEST_DIR}/download)
set(GTEST_SRC_DIR ${GTEST_DIR}/gtest)
set(GTEST_BUILD_DIR ${GTEST_DIR}/build)

# Download and unpack googletest at configure time
configure_file(${GTEST_DIR}/CMakeLists.txt ${GTEST_DL_DIR}/CMakeLists.txt)

execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${GTEST_DL_DIR}
)
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${GTEST_DL_DIR}
)
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(
  ${GTEST_SRC_DIR}
  ${GTEST_BUILD_DIR}
  EXCLUDE_FROM_ALL
)

# Add include path
include_directories(${GTEST_SRC_DIR}/googletest/include)

#
# AP library dependency
#

# Path to AP directories
set(AP_DIR ${ROOT_SRC_DIR}/ap)
set(AP_DL_DIR ${AP_DIR}/download)
set(AP_SRC_DIR ${AP_DIR}/ap)

# Download and unpack ap at configure time
configure_file(${AP_DIR}/CMakeLists.txt ${AP_DL_DIR}/CMakeLists.txt)

execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${AP_DL_DIR}
)
if(result)
  message(FATAL_ERROR "CMake step for ap failed: ${result}")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${AP_DL_DIR}
)
if(result)
  message(FATAL_ERROR "Build step for ap failed: ${result}")
endif()

# Add include path
include_directories(${AP_DIR})

file(GLOB_RECURSE AP_SRC 
"${AP_DIR}/*.cpp")

#
# chronometer library dependency
#

# Path to chronometer directories
set(TIME_DIR ${ROOT_SRC_DIR}/chronometer)
set(TIME_DL_DIR ${TIME_DIR}/download)
set(TIME_SRC_DIR ${TIME_DIR}/chronometer)

# Download and unpack time at configure time
configure_file(${TIME_DIR}/CMakeLists.txt ${TIME_DL_DIR}/CMakeLists.txt)

execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${TIME_DL_DIR}
)
if(result)
  message(FATAL_ERROR "CMake step for chronometer failed: ${result}")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${TIME_DL_DIR}
)
if(result)
  message(FATAL_ERROR "Build step for chronometer failed: ${result}")
endif()

# Add include path
include_directories(${TIME_DIR})

#
# flex_debug library dependency
#

# Path to flex_debug directories
set(FLEX_DIR ${ROOT_SRC_DIR}/flex_debug)
set(FLEX_DL_DIR ${FLEX_DIR}/download)
set(FLEX_SRC_DIR ${FLEX_DIR}/flex_debug)

# Download and unpack time at configure time
configure_file(${FLEX_DIR}/CMakeLists.txt ${FLEX_DL_DIR}/CMakeLists.txt)

execute_process(
  COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${FLEX_DL_DIR}
)
if(result)
  message(FATAL_ERROR "CMake step for flex_debug failed: ${result}")
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${FLEX_DL_DIR}
)
if(result)
  message(FATAL_ERROR "Build step for flex_debug failed: ${result}")
endif()

# Add include path
include_directories(${FLEX_DIR})
