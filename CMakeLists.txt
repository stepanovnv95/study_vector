cmake_minimum_required(VERSION 3.16)
project(study_vector)

set(CMAKE_CXX_STANDARD 17)

include(cmake/googletest.cmake)

add_executable(
        study_vector_tests
        vector.h
        StudyVectorTest.cpp
)
target_link_libraries(study_vector_tests gtest_main)
add_test(NAME example_test COMMAND example)
