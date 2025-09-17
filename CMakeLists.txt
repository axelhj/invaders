cmake_minimum_required(VERSION 3.21)

project(sce LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_CXX_COMPILER "g++")

set(CMAKE_CXX_FLAGS "-I${PROJECT_SOURCE_DIR} -I${PROJECT_SOURCE_DIR}\\deps\\SDL\\include -I${PROJECT_SOURCE_DIR}\\deps\\SDL_ttf\\include")

# set ("SDLLIBS", "-Wl,-Bstatic `sdl-config --static-libs` -Wl,-Bdynamic")

file(GLOB_RECURSE headers RELATIVE ${PROJECT_SOURCE_DIR} impl/**/*.h impl/*.h)
file(GLOB_RECURSE sources RELATIVE ${PROJECT_SOURCE_DIR} impl/**/*.cpp impl/*.cpp)

add_executable("sce" ${sources})
target_include_directories("sce" INTERFACE ${PROJECT_SOURCE_DIR})
target_sources("sce" PRIVATE FILE_SET headers BASE_DIRS TYPE HEADERS)

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
        ${PROJECT_SOURCE_DIR}/deps/SDL/build/libSDL3.dll.a
)
set_target_properties(
        "sdl"
        PROPERTIES IMPORTED_LOCATION
        ${PROJECT_SOURCE_DIR}/deps/SDL/build/libSDL3.dll
)

# ADDITIONAL SDL ttf
add_library("sdlttf" SHARED IMPORTED)
target_include_directories("sdlttf" INTERFACE deps/SDL_ttf/include)
set_target_properties(
        "sdlttf"
        PROPERTIES IMPORTED_IMPLIB
        ${PROJECT_SOURCE_DIR}/deps/SDL_ttf/build/libSDL3_ttf.dll.a
)
set_target_properties(
        "sdlttf"
        PROPERTIES IMPORTED_LOCATION
        ${PROJECT_SOURCE_DIR}/deps/SDL_ttf/build/libSDL3_ttf.dll
)

target_compile_options("sce" PRIVATE "-Wall")
target_compile_options("sce" PRIVATE "-O0")
target_compile_options("sce" PRIVATE "-m64")
target_compile_options("sce" PRIVATE "-g")
target_compile_options("sce" PRIVATE "-finput-charset=UTF-8")

target_link_options("sce" PRIVATE "-m64")
target_link_libraries("sce" "sdl" "sdlttf")
target_link_libraries("sce" "opengl32" "-lglu32" "-lgdi32")

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
        enable_testing()
        include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
        add_subdirectory(test)
endif()
