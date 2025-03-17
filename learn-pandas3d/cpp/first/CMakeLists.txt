cmake_minimum_required(VERSION 3.19)

SET(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for Mac OS X" FORCE)

project(App VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(p3framework SHARED IMPORTED)
set_property(TARGET p3framework PROPERTY
             IMPORTED_LOCATION "/Library/Developer/Panda3D/lib/libp3framework.dylib")

add_library(panda SHARED IMPORTED)
set_property(TARGET panda PROPERTY
        IMPORTED_LOCATION "/Library/Developer/Panda3D/lib/libpanda.dylib")
             
add_library(pandaexpress SHARED IMPORTED)
set_property(TARGET pandaexpress PROPERTY
            IMPORTED_LOCATION "/Library/Developer/Panda3D/lib/libpandaexpress.dylib")
            
add_library(p3dtoolconfig SHARED IMPORTED)
set_property(TARGET p3dtoolconfig PROPERTY
                IMPORTED_LOCATION "/Library/Developer/Panda3D/lib/libp3dtoolconfig.dylib")

add_library(p3dtool SHARED IMPORTED)
set_property(TARGET p3dtool PROPERTY
                IMPORTED_LOCATION "/Library/Developer/Panda3D/lib/libp3dtool.dylib")

add_library(p3direct SHARED IMPORTED)
set_property(TARGET p3direct PROPERTY
                IMPORTED_LOCATION "/Library/Developer/Panda3D/lib/libp3direct.dylib")

add_executable(App first.cpp)
target_include_directories(App PRIVATE "/Library/Developer/Panda3D/include")
target_link_libraries(App p3framework panda pandaexpress p3dtoolconfig p3dtool p3direct)
