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

add_library(renderer SHARED gfx.cpp)
target_link_libraries(renderer PUBLIC OpenGL::GL glfw glew "-framework Cocoa" "-framework IOKit")
target_include_directories(renderer SYSTEM PUBLIC "/usr/local/include")
target_include_directories(renderer PUBLIC "./include")
