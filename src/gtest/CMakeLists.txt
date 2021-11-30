cmake_minimum_required(VERSION 2.8.12)

project(googletest-download NONE)

include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           master
  SOURCE_DIR        "${GTEST_SRC_DIR}"
  BINARY_DIR        "${GTEST_BUILD_DIR}"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
  UPDATE_DISCONNECTED True
)
