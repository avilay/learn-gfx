cmake_minimum_required(VERSION 3.30)
project(raylib_demos C)

set(CMAKE_C_STANDARD 17)

find_package(raylib 4.5.0 REQUIRED)

message("Hello")
message(${PROJECT_NAME})
message(${raylib_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} main.c
        log_demo.c
        demos.h
        background_demo.c
        texture_demo.c
        raw_texture.c
        anim_demo.c
        button_demo.c
        explosion_demo.c
        screen_demo.c
        gesture_demo.c
        camera_demo.c
        utils.h
        utils.c
        user_input_demo.c
        collision_demo.c
        loading_thread.c
)
target_link_libraries(${PROJECT_NAME} raylib)
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})