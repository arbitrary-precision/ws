cmake_minimum_required(VERSION 2.8.12)

project(flex_debug NONE)

include(ExternalProject)
ExternalProject_Add(flex_debug
  GIT_REPOSITORY    https://github.com/Deohayer/flex_debug.git
  GIT_TAG           master
  SOURCE_DIR        "${FLEX_SRC_DIR}"
  BINARY_DIR        ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
