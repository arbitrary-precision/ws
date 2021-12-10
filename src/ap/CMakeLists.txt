cmake_minimum_required(VERSION 2.8.12)

project(ap NONE)

include(ExternalProject)
ExternalProject_Add(ap
  GIT_REPOSITORY    https://github.com/arbitrary-precision/ap.git
  GIT_TAG           pedantic
  SOURCE_DIR        "${AP_SRC_DIR}"
  BINARY_DIR        ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
  UPDATE_DISCONNECTED True
)
