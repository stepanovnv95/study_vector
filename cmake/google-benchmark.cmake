cmake_minimum_required(VERSION 3.16)

project(google-benchmark)

# Download and unpack at configure time
configure_file(${CMAKE_CURRENT_LIST_DIR}/google-benchmark-download.cmake google-benchmark-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/google-benchmark-download )
if(result)
    message(FATAL_ERROR "CMake step for google-benchmark failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/google-benchmark-download )
if(result)
    message(FATAL_ERROR "Build step for google-benchmark failed: ${result}")
endif()

add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/google-benchmark-src
        ${CMAKE_CURRENT_BINARY_DIR}/google-benchmark-build
        EXCLUDE_FROM_ALL)
