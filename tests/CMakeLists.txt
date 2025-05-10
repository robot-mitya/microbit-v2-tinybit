cmake_minimum_required(VERSION 3.10)
project(string_utils_tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(tests test_string_utils.cpp)

target_include_directories(tests PRIVATE ../)

# Enable color output
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)
endif()
