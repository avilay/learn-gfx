cmake_minimum_required(VERSION 3.17)

project(OpenGLSample VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

find_package(OpenGL REQUIRED)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION "/usr/local/lib/libglfw3.a"
    PUBLIC_HEADER "/usr/local/include/GLFW/glfw3.h"
)

add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES
    IMPORTED_LOCATION "/usr/local/lib/libGLEW.a"
    PUBLIC_HEADER "/usr/local/include/GL/glew.h"
)

add_executable(app app.cpp)
target_link_libraries(app PUBLIC OpenGL::GL glfw glew "-framework Cocoa" "-framework IOKit")
target_include_directories(app SYSTEM PUBLIC "/usr/local/include")
