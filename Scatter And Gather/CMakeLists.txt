cmake_minimum_required(VERSION 3.3)


project(m3 C)
set(CMAKE_C_STANDARD 99)

find_package(MPI)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(m3 Milestone_4.c)

target_link_libraries(m3 ${MPI_C_LIBRARIES})