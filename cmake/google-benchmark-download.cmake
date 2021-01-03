cmake_minimum_required(VERSION 3.16)

project(google-benchmark-download)

include(ExternalProject)
ExternalProject_Add(google-benchmark
    GIT_REPOSITORY    https://github.com/google/benchmark.git
    GIT_TAG           master
    SOURCE_DIR        "${CMAKE_CURRENT_BINARY_DIR}/google-benchmark-src"
    BINARY_DIR        "${CMAKE_CURRENT_BINARY_DIR}/google-benchmark-build"
    CONFIGURE_COMMAND ""
    BUILD_COMMAND     ""
    INSTALL_COMMAND   ""
    TEST_COMMAND      ""
)
