cmake_minimum_required(VERSION 3.16)

include(cmake/googletest.cmake)
include(cmake/google-benchmark.cmake)

project(study_vector)
set(CMAKE_CXX_STANDARD 17)

add_executable(
        study_vector_tests
        vector.h
        mocks.h
        tests.cpp
)
target_link_libraries(study_vector_tests gtest_main)
add_test(NAME example_test COMMAND example)

add_executable(
        study_vector_benchmark
        vector.h
        benchmark.cpp
)
target_link_libraries(study_vector_benchmark benchmark::benchmark)
