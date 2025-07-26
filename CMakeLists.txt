cmake_minimum_required(VERSION 3.28)
project(block_test_client)
set(CMAKE_CXX_STANDARD 20)
include_directories(.)
add_subdirectory(test_client/TestKit-pp)
add_executable(block_test_client test_client/main.cpp)

add_library(BlockTest test_client/BlockTest.cpp)
target_link_libraries(block_test_client TestKit BlockTest)