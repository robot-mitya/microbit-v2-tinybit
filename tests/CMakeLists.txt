cmake_minimum_required(VERSION 3.10)
project(mimi_tests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(tests
        main.cpp
        ../source/mimi/icom_controller.cpp
        ../source/mimi/ilanguage_controller.cpp
        ../source/mimi/icore.cpp
)

target_include_directories(tests PRIVATE ../source)

# Enable color output
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)
endif()
