cmake_minimum_required(VERSION 2.8.12)

project(chronometer NONE)

include(ExternalProject)
ExternalProject_Add(chronometer
  GIT_REPOSITORY    https://github.com/Deohayer/chronometer.git
  GIT_TAG           master
  SOURCE_DIR        "${TIME_SRC_DIR}"
  BINARY_DIR        ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
