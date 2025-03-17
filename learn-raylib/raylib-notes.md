# Raylib Running Notes

## Building Raylib Itself

To build from source -

```shell
cmake -G Ninja -DPLATFORM=Web -S . -B build
cmake --build build
```

To build WASM friendly lib from source -

First ensure that `emsdk` is installed

```shell
emcmake cmake -G Ninja -DPLATFORM=Web -S . -B web-build
cmake --build web-build
```

## Building My Projects

Ref: https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)

### OS Native Project

When I install the `raylib` package, it is installed as a cmake package so for usual OS-native builds all I have to do is -

```cmake
find_package(raylib 4.5.0 REQUIRED)
target_link_libraries(${PROJECT_NAME} raylib)
```

### Web Project

**Running Notes for C++**

When building a C++ project using raylib I ran into the following issues -

* ==Do not use Ninja build== even though the documentation says to. This will run a utility called `clang-scan-deps` which will invariably throw an error. Ensure that no `-G` flag is given to `cmake`. This will ensure that `cmake` which decide which underlying build system to use. The default build system works just fine.
* Typically `raylib.h` resides in `/usr/include/raylib.h`. When I am compiling C++ projects with C header files the  order of includes is very important. All the C++ includes must come before the C includes. When using `target_include_directories` or `inculde_directories`, CMake documentation says that these directories will always be appended to the system includes, but that does not seem to be the case. It simply adds a `-I` flag with the dirs, which makes them appear before the emscripten system includes. Verify this by running `emcc -xc++ -E -v -idirafter /usr/include -`. If I can somehow configure CMake to use the `-idirafter` compiler option instead of `-I` option, things would work. Again verify this by running `emcc -xc++ -E -v -idirafter /usr/include -`. But I could not find an easy way to do this. There are several workarounds to this -
  * Copy the raylib header files (raylib.h, raymath.h, and rlgl.h) locally and include them with quotes instead of angle brackets. These files are available in the wasm build directory of raylib under include. This will also work for native builds as long as raylib generates the same include files for both wasm and default. Otherwise I can wrap the quoted includes inside `#ifdef`.
  * Another workaround is to copy `raylib.h` to one of the default include paths of `emcc`. I can see the path list by running either of the above two commands. At the time of this writing (12/2024) the paths are -


  1. `$EMSDKHOME/upstream/emscripten/cache/sysroot/include/fakesdl`
  2. `$EMSDKHOME/upstream//emscripten/cache/sysroot/include/compat`
  3. `$EMSDKHOME/upstream//emscripten/cache/sysroot/include/c++/v1`
  4. `$EMSDKHOME/upstream//lib/clang/20/include$EMSDKHOME/upstream//emscripten/cache/sysroot/include`
* On the CLI I can configure CMake builds by running `emcmake cmake -S . -B web-build`. All this does is to add a toolchain option to the `cmake` invocation `cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/emsdk/Emscripten.cmake`.  So when running from IDE all I have to do is add this same toolchain CMake Options. Usually the toolchain can be found at `/path/to/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake`
* I do need to pass a bunch of CXX flags that I can either pass in as build options or set them in the CMakeLists.txt file. 
  * `-s USE_GLFW=3`
  * `-s WASM=1`
  * `-s ASYNCIFY`
  * `-s GL_ENABLE_GET_PROC_ADDRESS=1`


#### tl;dr

Use the following options when configuring the cmake build -

```shell
-DCMAKE_TOOLCHAIN_FILE=/home/avilay/projects/cloned/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
-DCMAKE_C_FLAGS="-Wall -s USE_GLFW=3 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1"
-G Ninja
```

Call the following functions inside the CMakeLists.txt file -

```cmake
target_compile_definitions(${PROJECT_NAME} PUBLIC -DPLATFORM_WEB)
set(CMAKE_EXECUTABLE_SUFFIX ".html")

target_include_directories(${PROJECT_NAME} PUBLIC "/usr/include" "/path/to/emsdk/repo/upstream/emscripten/cache/sysroot/include")

add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION "/path/to/wasm/friendly/libraylib.a")
```

#### Set the toolchain file

```shell
DCMAKE_TOOLCHAIN_FILE=/home/avilay/projects/cloned/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake
```

A simple way to set this is when configuring the cmake build -

```shell
cmake -DCMAKE_TOOLCHAIN_FILE=<path> -S . -B web-build
```

#### Specify special linker flags

```
-s USE_GLFW=3
-s WASM=1
-s ASYNCIFY
-s GL_ENABLE_GET_PROC_ADDRESS=1
```

If I am using the same CMake file for both OS-native and web builds, then I can set these inside the CMakeLists.txt as follows -

```cmake
if (EMSCRIPTEN)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1 -s GL_ENABLE_GET_PROC_ADDRESS=1")
endif()
```

#### Add a compile definition

```
DPLATFORM_WEB
```

This can be done as yet another c-flag `-DPLATFORM_WEB` or using the `target_compile_definitions` CMake function -

```cmake
target_compile_definitions(${PROJECT_NAME} PUBLIC -DPLATFORM_WEB)
```

I can include this inside the `EMSCRIPTEN` if condition.

#### Set .html as the output

This will generate an html file with the default emscripten shell that can be overridden. If I only want the WASM and javascript files that I can include in my html I don't have to do this. But it serves as a good example of how to include WASM executables in HTMLs.

```cmake
set(CMAKE_EXECUTABLE_SUFFIX ".html")
```

#### Add emscripten include files

```cmake
target_include_directories(${PROJECT_NAME} PUBLIC "/usr/include" "/path/to/emsdk/repo/upstream/emscripten/cache/sysroot/include")
```

I think I have to give the `/usr/include` because I am specifying custom include directories.

#### Add raylib without cmake support

The raylib that I compiled above will typically be inside the raylib source directory somewhere. It is not available as a cmake package like regular raylib. I have to do the following to link it -

```cmake
add_library(raylib STATIC IMPORTED)
set_target_properties(raylib PROPERTIES IMPORTED_LOCATION "/full/path/to/libraylib.a")
```

#### Additional Flags

Use these as needed -

```
// Specify a resources directory for data compilation (it will generate a .data file)
--preload-file resources

// Specify a heap memory size in bytes (default = 16MB) (67108864 = 64MB)
-s TOTAL_MEMORY=67108864

// Allow automatic heap memory resizing -> NOT RECOMMENDED!
-s ALLOW_MEMORY_GROWTH=1

// Force filesystem creation to load/save files data (for example if you need to support save-game or drag&drop files)
-s FORCE_FILESYSTEM=1

// Enable runtime checks for common memory allocation errors (-O1 and above turn it off)
-s ASSERTIONS=1

// Include information for code profiling
--profiling
```



Camera target and offset was initially confusing, but here is what my experiments have shown me - offset are the screen coordinates where the target will be placed. However there is nothing stopping me from setting the offset to off-screen. The target just won't be visible to me, but the math keeps working out. See `camera-experiments`.

#### Examples to check out

* [x] Raylib colors palette is a useful reference, no need to implement it.
* [x] Custom logging
* [ ] ~~Storage values~~: I am better off using glib2 hash tables and file i/o.
* [ ] ~~Drop files~~: This is about how to drop files on the game window and have the game load and read it.
* [x] Random values: A useful utility function called `int GetRandomValue(int min, int max)` to generate integers between $[min, max]$.
* [x] Basic shapes: I can draw circles, rectangles, triangles, and polygons - with solid fill color, gradient fill color, or no fill color.
* [x] Format text: A useful little function `const char* TextFormat(const char* text, ...)` which takes a format string and some variables and returns a formatted string.
* [x] Background scrolling
* [x] Logo raylib (this is a texture)
* [x] Checked texture generated by code and raw image loading
* [x] Sprite anim
* [x] Sprite button
* [x] Sprite explosion
* [ ] ~~Gif player~~ This is not the recommended way to do anim, use sprite sheets instead as demoed in sprite anim.
* [x] Collision areas
* [ ] 2D camera platformer
* [ ] ~~Smooth pixel perfect~~
* [x] Loading thread
* [ ] Raylib fonts

