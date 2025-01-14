cmake_minimum_required(VERSION 3.3)


project(micro_proj_M2 C)
set(CMAKE_C_STANDARD 99)

find_package(MPI)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(micro_proj_M2 Milestone_2.c)

target_link_libraries(micro_proj_M2 ${MPI_C_LIBRARIES})