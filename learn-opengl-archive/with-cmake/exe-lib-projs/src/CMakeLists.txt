find_package(OpenGL REQUIRED)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION "/usr/local/lib/libglfw3.a"
)

add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES
    IMPORTED_LOCATION "/usr/local/lib/libGLEW.a"
)

add_library(gfx STATIC renderer.cpp "../include/gfx/gfx.h")
target_link_libraries(gfx PRIVATE OpenGL::GL glfw glew "-framework Cocoa" "-framework IOKit")
target_include_directories(gfx PUBLIC "../include")
