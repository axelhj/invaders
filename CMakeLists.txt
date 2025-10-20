cmake_minimum_required(VERSION 3.21)

project(invaders LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}/deps/SDL/include -I${PROJECT_SOURCE_DIR}/deps/SDL_ttf/include")

# set ("SDLLIBS", "-Wl,-Bstatic `sdl-config --static-libs` -Wl,-Bdynamic")

file(GLOB_RECURSE headers RELATIVE ${PROJECT_SOURCE_DIR} impl/**/*.h impl/*.h)
file(GLOB_RECURSE sources RELATIVE ${PROJECT_SOURCE_DIR} impl/**/*.cpp impl/*.cpp)

add_executable("invaders" ${sources})
target_include_directories("invaders" INTERFACE ${PROJECT_SOURCE_DIR})
target_include_directories("invaders" PRIVATE ${PROJECT_SOURCE_DIR}/deps/stb_image)
target_sources("invaders" PRIVATE FILE_SET headers BASE_DIRS TYPE HEADERS)

include(CMakePrintHelpers)
cmake_print_variables(headers)
cmake_print_variables(sources)
# cmake_print_variables(CMAKE_CXX_FLAGS)

# ADEQUATE SDL
add_library("sdl" SHARED IMPORTED)
target_include_directories("sdl" INTERFACE deps/SDL/include)
set_target_properties(
        "sdl"
        PROPERTIES IMPORTED_IMPLIB
        ${PROJECT_SOURCE_DIR}/deps/SDL/build/libSDL3.a
)
set_target_properties(
        "sdl"
        PROPERTIES IMPORTED_LOCATION
        ${PROJECT_SOURCE_DIR}/deps/SDL/build/libSDL3.a
)

# ADDITIONAL SDL ttf
add_library("sdlttf" SHARED IMPORTED)
target_include_directories("sdlttf" INTERFACE deps/SDL_ttf/include)
set_target_properties(
        "sdlttf"
        PROPERTIES IMPORTED_IMPLIB
        ${PROJECT_SOURCE_DIR}/deps/SDL_ttf/build/libSDL3_ttf.a
)
set_target_properties(
        "sdlttf"
        PROPERTIES IMPORTED_LOCATION
        ${PROJECT_SOURCE_DIR}/deps/SDL_ttf/build/libSDL3_ttf.a
)

target_compile_options("invaders" PRIVATE "-Wall")
target_compile_options("invaders" PRIVATE "-O0")
# target_compile_options("invaders" PRIVATE "-m64")
target_compile_options("invaders" PRIVATE "-g")
target_compile_options("invaders" PRIVATE "-finput-charset=UTF-8")
# target_link_options("invaders" PRIVATE "-m64")
target_link_libraries(
        "invaders"
        "sdl"
        "sdlttf"
)
# target_link_libraries("invaders" "opengl32" "-lglu32" "-lgdi32")

target_link_libraries(
        "invaders"
        "-Wl,-framework,Cocoa"
        "-Wl,-framework,IOKit"
        "-Wl,-framework,ForceFeedback"
        "-Wl,-framework,Carbon"
        "-Wl,-framework,CoreAudio"
        "-Wl,-framework,AudioToolbox"
        "-Wl,-framework,AVFoundation"
        "-Wl,-framework,CoreBluetooth"
        "-Wl,-framework,CoreGraphics"
        "-Wl,-framework,CoreMotion"
        "-Wl,-framework,Foundation"
        "-Wl,-weak_framework,GameController"
        "-Wl,-weak_framework,Metal"
        "-Wl,-weak_framework,QuartzCore"
        "-Wl,-weak_framework,CoreHaptics"
        "-Wl,-framework,CoreVideo"
        "-Wl,-framework,CoreMedia"
        "-Wl,-framework,CoreText"
        "-Wl,-framework,CoreFoundation"
        "-weak_framework UniformTypeIdentifiers"
        "-L/opt/homebrew/lib"
        "freetype"
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
        enable_testing()
        include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
        add_subdirectory(test)
endif()
