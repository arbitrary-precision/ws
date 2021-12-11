cmake_minimum_required(VERSION 2.9)

project(ap_workspace)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Release)

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
set(BOOST_SRC_DIR ${ROOT_SRC_DIR})

# Add include path.
include_directories(${BOOST_SRC_DIR})

message(STATUS "foo include dir: ${BOOST_SRC_DIR}")

#
# Subproject - measure.
#

set(MEASURE_SRC_DIR ${ROOT_SRC_DIR}/measure)
set(
  MEASURE_SRC_FILES
  ${AP_SRC_FILES}
  ${MEASURE_SRC_DIR}/measure.cpp
)
add_executable(measure ${MEASURE_SRC_FILES})
target_compile_options(measure PUBLIC
  -DAP_WORD=unsigned\ long\ long
  -DAP_DWORD=unsigned\ __int128
  )

#
# Subproject - validate.
#

set(VALIDATE_SRC_DIR ${ROOT_SRC_DIR}/validate)
set(
  VALIDATE_SRC_FILES
  ${AP_SRC_FILES}
  # core
  ${VALIDATE_SRC_DIR}/common.cpp
  ${VALIDATE_SRC_DIR}/core/dregister.cpp
  ${VALIDATE_SRC_DIR}/core/fregister.cpp
  ${VALIDATE_SRC_DIR}/array/array.cpp
  ${VALIDATE_SRC_DIR}/integer_handle/integer_handle.cpp
  # asm-level API
  ${VALIDATE_SRC_DIR}/asm/add.cpp
  ${VALIDATE_SRC_DIR}/asm/bit.cpp
  ${VALIDATE_SRC_DIR}/asm/cmp.cpp
  ${VALIDATE_SRC_DIR}/asm/cmpres.cpp
  ${VALIDATE_SRC_DIR}/asm/cp.cpp
  ${VALIDATE_SRC_DIR}/asm/div_short.cpp
  ${VALIDATE_SRC_DIR}/asm/div.cpp
  ${VALIDATE_SRC_DIR}/asm/fill.cpp
  ${VALIDATE_SRC_DIR}/asm/lsh.cpp
  ${VALIDATE_SRC_DIR}/asm/mul_short.cpp
  ${VALIDATE_SRC_DIR}/asm/mul.cpp
  ${VALIDATE_SRC_DIR}/asm/trim.cpp
  ${VALIDATE_SRC_DIR}/asm/not.cpp
  ${VALIDATE_SRC_DIR}/asm/rsh.cpp
  ${VALIDATE_SRC_DIR}/asm/sub.cpp
  ${VALIDATE_SRC_DIR}/asm/twos.cpp
  # int-level API
  ${VALIDATE_SRC_DIR}/integer_api/add.cpp
  ${VALIDATE_SRC_DIR}/integer_api/and.cpp
  ${VALIDATE_SRC_DIR}/integer_api/cmp.cpp
  ${VALIDATE_SRC_DIR}/integer_api/fbasic.cpp
  ${VALIDATE_SRC_DIR}/integer_api/fstr.cpp
  ${VALIDATE_SRC_DIR}/integer_api/lsh.cpp
  ${VALIDATE_SRC_DIR}/integer_api/mul.cpp
  ${VALIDATE_SRC_DIR}/integer_api/not.cpp
  ${VALIDATE_SRC_DIR}/integer_api/or.cpp
  ${VALIDATE_SRC_DIR}/integer_api/quo.cpp
  ${VALIDATE_SRC_DIR}/integer_api/rem.cpp
  ${VALIDATE_SRC_DIR}/integer_api/rsh.cpp
  ${VALIDATE_SRC_DIR}/integer_api/scp.cpp
  ${VALIDATE_SRC_DIR}/integer_api/sub.cpp
  ${VALIDATE_SRC_DIR}/integer_api/tbasic.cpp
  ${VALIDATE_SRC_DIR}/integer_api/tos.cpp
  ${VALIDATE_SRC_DIR}/integer_api/tou.cpp
  ${VALIDATE_SRC_DIR}/integer_api/tstr.cpp
  ${VALIDATE_SRC_DIR}/integer_api/xor.cpp
  # user-level API
  ${VALIDATE_SRC_DIR}/integer/add.cpp
  ${VALIDATE_SRC_DIR}/integer/and.cpp
  ${VALIDATE_SRC_DIR}/integer/basic.cpp
  ${VALIDATE_SRC_DIR}/integer/cmp.cpp
  ${VALIDATE_SRC_DIR}/integer/copy.cpp
  ${VALIDATE_SRC_DIR}/integer/ctor.cpp
  ${VALIDATE_SRC_DIR}/integer/dec.cpp
  ${VALIDATE_SRC_DIR}/integer/inc.cpp
  ${VALIDATE_SRC_DIR}/integer/lsh.cpp
  ${VALIDATE_SRC_DIR}/integer/move.cpp
  ${VALIDATE_SRC_DIR}/integer/mul.cpp
  ${VALIDATE_SRC_DIR}/integer/quo.cpp
  ${VALIDATE_SRC_DIR}/integer/not.cpp
  ${VALIDATE_SRC_DIR}/integer/or.cpp
  ${VALIDATE_SRC_DIR}/integer/rem.cpp
  ${VALIDATE_SRC_DIR}/integer/rsh.cpp
  ${VALIDATE_SRC_DIR}/integer/str.cpp
  ${VALIDATE_SRC_DIR}/integer/sub.cpp
  ${VALIDATE_SRC_DIR}/integer/usgn.cpp
  ${VALIDATE_SRC_DIR}/integer/xor.cpp
  )

add_executable(validate8 ${VALIDATE_SRC_FILES})
target_compile_options(validate8 PUBLIC
  -DAP_WORD=unsigned\ char
  -DAP_WORD_SIZE=1
  -DAP_DWORD=unsigned\ short
  -DAP_DWORD_SIZE=2
  -O0
  )
target_link_libraries(validate8 gtest_main)

add_executable(validate16 ${VALIDATE_SRC_FILES})
target_compile_options(validate16 PUBLIC
  -DAP_WORD=unsigned\ short
  -DAP_WORD_SIZE=2
  -DAP_DWORD=unsigned
  -DAP_DWORD_SIZE=4
  -O0
  )
target_link_libraries(validate16 gtest_main)

add_executable(validate32 ${VALIDATE_SRC_FILES})
target_compile_options(validate32 PUBLIC
  -DAP_WORD=unsigned
  -DAP_WORD_SIZE=4
  -DAP_DWORD=unsigned\ long\ long
  -DAP_DWORD_SIZE=8
  -O0
  )
target_link_libraries(validate32 gtest_main)

add_executable(validatehpp ${VALIDATE_SRC_FILES})
target_compile_options(validatehpp PUBLIC
  -O0
  )
target_link_libraries(validatehpp gtest_main)

add_executable(validatecpp ${VALIDATE_SRC_FILES})
target_compile_options(validatecpp PUBLIC
  -DAP_USE_SOURCES
  -O0
  )
target_link_libraries(validatecpp gtest_main)

#
# Target for memory leak testing via valgrind.
#

add_custom_target(
  test8
  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out-8.txt ./validate8 --gtest_break_on_failure
  )
add_dependencies(test8 validate8)

add_custom_target(
  test16
  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out-16.txt ./validate16 --gtest_break_on_failure
  )
add_dependencies(test16 validate16)

add_custom_target(
  test32
  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out-32.txt ./validate32 --gtest_break_on_failure
  )
add_dependencies(test32 validate32)

add_custom_target(
  testhpp
  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out-hpp.txt ./validatehpp --gtest_break_on_failure
  )
add_dependencies(testhpp validatehpp)

add_custom_target(
  testcpp
  valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out-cpp.txt ./validatecpp --gtest_break_on_failure
  )
add_dependencies(testcpp validatecpp)

add_custom_target(
  testw
  )
add_dependencies(testw test8 test16 test32)

add_custom_target(
  testa
  )
add_dependencies(testa test8 test16 test32 testhpp testcpp)