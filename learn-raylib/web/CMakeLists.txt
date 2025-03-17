cmake_minimum_required(VERSION 3.30)
project(web C)

set(CMAKE_C_STANDARD 17)

set(RESOURCES "/home/avilay/projects/bitbucket/learn/learn-gfx/learn-raylib/web/resources")

add_executable(${PROJECT_NAME} main.c)

target_compile_definitions(${PROJECT_NAME} PUBLIC -DPLATFORM_WEB)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --preload-file ${RESOURCES}")
set(CMAKE_EXECUTABLE_SUFFIX ".html")

#target_include_directories(${PROJECT_NAME} PUBLIC "/usr/include" "/home/avilay/projects/cloned/emsdk/upstream/emscripten/cache/sysroot/include")
target_include_directories(${PROJECT_NAME} PUBLIC "/usr/include")
add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION "/home/avilay/projects/cloned/detached/raylib-5.5/raylib/web-build/raylib/libraylib.a")

target_link_libraries(${PROJECT_NAME} raylib)
