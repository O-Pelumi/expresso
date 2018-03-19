cmake_minimum_required(VERSION 3.16)
project(expresso)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(expresso STATIC ${SRC_FILES})

enable_testing()
add_subdirectory(tests)
