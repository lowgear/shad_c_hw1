cmake_minimum_required(VERSION 3.12)
project(shad_c_hw1 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

add_executable(runTests tests.cc number_operations.c str_ops.c)
add_executable(main main.c number_operations.c str_ops.c)

target_link_libraries(runTests)
