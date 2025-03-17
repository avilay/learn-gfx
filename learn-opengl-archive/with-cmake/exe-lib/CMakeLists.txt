cmake_minimum_required(VERSION 3.17)

project(OpenGLSample VERSION 0.0.2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

add_subdirectory(renderer)
add_executable(OpenGLSample app.cpp)
target_link_libraries(OpenGLSample PUBLIC renderer)
