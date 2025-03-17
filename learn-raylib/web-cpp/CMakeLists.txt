cmake_minimum_required(VERSION 3.30)
project(web-cpp)

set(CMAKE_CXX_STANDARD 20)

set(RESOURCES "/home/avilay/projects/bitbucket/learn/learn-gfx/learn-raylib/web-cpp/resources")

add_executable(${PROJECT_NAME} main.cpp
        Background.cpp
        Background.h)

if (EMSCRIPTEN)
    message("Building for web")

    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DPLATFORM_WEB)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file ${RESOURCES}")
    target_link_directories(${PROJECT_NAME} PUBLIC "/home/avilay/projects/cloned/detached/raylib-5.5/raylib/web-build/raylib")
else()
    message("Building for native OS")
    find_package(raylib 5.5.0 REQUIRED)
    file(COPY ${RESOURCES} DESTINATION ${CMAKE_BINARY_DIR})
endif()


target_link_libraries(${PROJECT_NAME} raylib)
