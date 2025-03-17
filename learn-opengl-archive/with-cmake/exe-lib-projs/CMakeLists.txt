cmake_minimum_required(VERSION 3.17)

project(FullDemo
    VERSION 0.0.1
    DESCRIPTION "Full demo with a library and an app"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED)

include_directories(SYSTEM PUBLIC "/usr/local/include")

add_subdirectory(src)
add_subdirectory(app)
