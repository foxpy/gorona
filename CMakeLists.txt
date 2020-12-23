cmake_minimum_required(VERSION 3.1)
project(Gorona)

add_subdirectory(qc)
add_subdirectory(game)
add_executable(gorona gorona.c)
target_link_libraries(gorona PUBLIC Game qc)
