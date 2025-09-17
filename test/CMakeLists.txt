#https://cmake.org/cmake/help/book/mastering-cmake/chapter/Testing%20With%20CMake%20and%20CTest.html

# Re-glob the system under test sources
file(GLOB_RECURSE headers RELATIVE ${PROJECT_SOURCE_DIR}/test ../impl/**/*.h ../impl/*.h)
file(GLOB_RECURSE sources RELATIVE ${PROJECT_SOURCE_DIR}/test ../impl/**/*.cpp ../impl/*.cpp)

list(REMOVE_ITEM sources ../impl/main.cpp)
list(REMOVE_ITEM headers ../impl/main.h)

cmake_print_variables(headers)
cmake_print_variables(sources)

add_executable("testproj" mytest.cpp;${sources})
target_include_directories("testproj" INTERFACE ${PROJECT_SOURCE_DIR})
target_sources("testproj" PRIVATE FILE_SET headers BASE_DIRS TYPE HEADERS)

target_compile_options("testproj" PRIVATE "-Wall")
target_compile_options("testproj" PRIVATE "-O0")
target_compile_options("testproj" PRIVATE "-m64")
target_compile_options("testproj" PRIVATE "-g")
target_compile_options("testproj" PRIVATE "-finput-charset=UTF-8")

target_link_options("testproj" PRIVATE "-m64")
target_link_libraries("testproj" "sdl" "sdlttf")
target_link_libraries("testproj" "opengl32" "-lglu32" "-lgdi32")
# add_test(NAME case_1 COMMAND testproj 1)
# add_test(NAME case_2 COMMAND testproj 2)
# add_test(NAME case_3 COMMAND testproj 3)
add_test(NAME case_4 COMMAND testproj 4)
# add_test(NAME TestName COMMAND ExecutableToRun arg0 arg2 ...)
