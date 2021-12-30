cmake_minimum_required(VERSION 3.16)

project(linux-commands-flashcards)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_BUILD_TYPE Debug)


#file(GLOB_RECURSE src_code ${PROJECT_SOURCE_DIR}/*.cpp)

file(GLOB_RECURSE src_code src/*.cpp)
include_directories(src/headers)

add_executable(flashcards ${src_code})