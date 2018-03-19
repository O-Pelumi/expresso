cmake_minimum_required(VERSION 3.16)
project(expressotest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(expressotest ${SRC_FILES})
target_link_libraries(expressotest expresso gtest gtest_main)

enable_testing()
add_subdirectory(googletest)
add_test(all_tests expressotest)
