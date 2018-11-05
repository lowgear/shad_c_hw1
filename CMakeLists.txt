cmake_minimum_required(VERSION 3.12)
project(shad_c_hw1 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

link_directories(lib)

add_executable(runTests tests.cc number_operations.c str_ops.c)
add_executable(main main.c number_operations.c str_ops.c)

target_link_libraries(runTests)
