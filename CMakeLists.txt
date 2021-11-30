cmake_minimum_required(VERSION 2.9)

project(ap_workspace)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

# Root directories.
set(ROOT_DIR ${CMAKE_CURRENT_BINARY_DIR}/..)
set(ROOT_SRC_DIR ${ROOT_DIR}/src)

#
# Dependency - Arbitrary Precision.
#

# Paths to AP directories.
set(AP_DIR ${ROOT_SRC_DIR}/ap)
set(AP_DL_DIR ${AP_DIR}/download)
set(AP_SRC_DIR ${AP_DIR}/ap)

# Download and unpack ap at configure time.
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

# Add include path.
include_directories(${AP_DIR})

file(GLOB_RECURSE AP_SRC_FILES 
"${AP_DIR}/*.cpp")

#
# Dependency - Google Test.
#

# Paths to Google Test directories.
set(GTEST_DIR ${ROOT_SRC_DIR}/gtest)
set(GTEST_DL_DIR ${GTEST_DIR}/download)
set(GTEST_SRC_DIR ${GTEST_DIR}/gtest)
set(GTEST_BUILD_DIR ${GTEST_DIR}/build)

# Download and unpack googletest at configure time.
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
# settings on Windows.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(
  ${GTEST_SRC_DIR}
  ${GTEST_BUILD_DIR}
  EXCLUDE_FROM_ALL
)

# Add include path.
include_directories(${GTEST_SRC_DIR}/googletest/include)

#
# Dependency - chronometer.
#

# Paths to chronometer directories.
set(TIME_DIR ${ROOT_SRC_DIR}/chronometer)
set(TIME_DL_DIR ${TIME_DIR}/download)
set(TIME_SRC_DIR ${TIME_DIR}/chronometer)

# Download and unpack time at configure time.
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

# Add include path.
include_directories(${TIME_DIR})

#
# Dependency - flex_debug.
#

# Paths to flex_debug directories.
set(FLEX_DIR ${ROOT_SRC_DIR}/flex_debug)
set(FLEX_DL_DIR ${FLEX_DIR}/download)
set(FLEX_SRC_DIR ${FLEX_DIR}/flex_debug)

# Download and unpack time at configure time.
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

# Add include path.
include_directories(${FLEX_DIR})

#
# Dependency - Boost.
#

# Path to Boost directory.
set(BOOST_SRC_DIR ${ROOT_SRC_DIR}/boost)

# Add include path.
include_directories(${BOOST_SRC_DIR})

#
# Subproject - validate.
#

set(VALIDATE_SRC_DIR ${ROOT_SRC_DIR}/validate)
set(
  VALIDATE_SRC_FILES
  ${AP_SRC_FILES}
  ${VALIDATE_SRC_DIR}/core/fregister.cpp
  ${VALIDATE_SRC_DIR}/core/wregister.cpp
  ${VALIDATE_SRC_DIR}/core/rregister.cpp
  ${VALIDATE_SRC_DIR}/array/array.cpp
  ${VALIDATE_SRC_DIR}/asm/cmpres.cpp
  ${VALIDATE_SRC_DIR}/asm/cmp.cpp
  ${VALIDATE_SRC_DIR}/asm/trim.cpp
  ${VALIDATE_SRC_DIR}/asm/cp.cpp
  ${VALIDATE_SRC_DIR}/asm/fill.cpp
  ${VALIDATE_SRC_DIR}/asm/twos.cpp
  ${VALIDATE_SRC_DIR}/asm/add.cpp
  ${VALIDATE_SRC_DIR}/asm/sub.cpp
  ${VALIDATE_SRC_DIR}/asm/mul.cpp
  ${VALIDATE_SRC_DIR}/asm/div.cpp
  ${VALIDATE_SRC_DIR}/asm/or.cpp
  ${VALIDATE_SRC_DIR}/asm/xor.cpp
  ${VALIDATE_SRC_DIR}/asm/and.cpp
  ${VALIDATE_SRC_DIR}/asm/not.cpp
  ${VALIDATE_SRC_DIR}/asm/rsh.cpp
  ${VALIDATE_SRC_DIR}/asm/lsh.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/add.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/and.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/cmp.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/div.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/fstr.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/lsh.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/mul.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/not.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/or.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/rsh.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/scp.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/sub.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/tstr.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/ucp.cpp
  ${VALIDATE_SRC_DIR}/int_alg/uint/xor.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/add.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/and.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/cmp.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/div.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/fstr.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/lsh.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/mul.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/not.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/or.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/rsh.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/scp.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/stou.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/sub.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/tstr.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/ucp.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/utos.cpp
  ${VALIDATE_SRC_DIR}/int_alg/sint/xor.cpp
  )

add_executable(validate8 ${VALIDATE_SRC_FILES})
target_compile_options(validate8 PUBLIC
  -DAP_USE_ASSERT
  -DAP_WORD=unsigned\ char
  -DAP_WORD_SIZE=1
  -DAP_DWORD=unsigned\ short
  -DAP_DWORD_SIZE=2
  )
target_link_libraries(validate8 gtest_main)

add_executable(validate16 ${VALIDATE_SRC_FILES})
target_compile_options(validate16 PUBLIC
  -DAP_USE_ASSERT
  -DAP_WORD=unsigned\ short
  -DAP_WORD_SIZE=2
  -DAP_DWORD=unsigned
  -DAP_DWORD_SIZE=4
  )
target_link_libraries(validate16 gtest_main)

add_executable(validate32 ${VALIDATE_SRC_FILES})
target_compile_options(validate32 PUBLIC
  -DAP_USE_ASSERT
  -DAP_WORD=unsigned
  -DAP_WORD_SIZE=4
  -DAP_DWORD=unsigned\ long\ long
  -DAP_DWORD_SIZE=8
  )
target_link_libraries(validate32 gtest_main)

add_executable(validatehpp ${VALIDATE_SRC_FILES})
target_compile_options(validatehpp PUBLIC
  -DAP_USE_ASSERT
  )
target_link_libraries(validatehpp gtest_main)

add_executable(validatecpp ${VALIDATE_SRC_FILES})
target_compile_options(validatecpp PUBLIC
  -DAP_USE_ASSERT
  -DAP_USE_SOURCES
  )
target_link_libraries(validatecpp gtest_main)

#
# Target for memory leak testing via valgrind.
#

add_custom_target(
  test8
  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./validate8
  )
add_dependencies(test8 validate8)

add_custom_target(
  test16
  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./validate16
  )
add_dependencies(test16 validate16)

add_custom_target(
  test32
  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./validate32
  )
add_dependencies(test32 validate32)

add_custom_target(
  testhpp
  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./validatehpp
  )
add_dependencies(testhpp validatehpp)

add_custom_target(
  testcpp
  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./validatecpp
  )
add_dependencies(testcpp validatecpp)

add_custom_target(
  testall
  )
add_dependencies(testall test8 test16 test32 testhpp testcpp)