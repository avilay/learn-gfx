cmake_minimum_required(VERSION 3.29)
project(camera_experiments C)

set(CMAKE_C_STANDARD 17)
find_package(raylib 4.5.0 EXACT)

add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} raylib)
