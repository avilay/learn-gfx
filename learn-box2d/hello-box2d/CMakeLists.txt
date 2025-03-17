cmake_minimum_required(VERSION 3.30)
project(hello_box2d C)

set(CMAKE_C_STANDARD 17)

add_library(box2d SHARED IMPORTED)
set_property(TARGET box2d PROPERTY IMPORTED_LOCATION /usr/lib/libbox2d.so)
target_include_directories(box2d INTERFACE /usr/include/box2d)

add_executable(hello_box2d main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE box2d m)
