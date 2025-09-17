# SCE

## Requirements
- freetype must be installed
- CMAKE 3.x is used
- g++ is required. The build config is only tested on Windows

## Build & run commands

### SDL

OpenGL_ES does not work in a default install so must be disabled. Since a static build is preferred, SDL_STATIC is enabled.
The SDL_ttf build depends on the SDL build but if the shared build is not configured, no target will be built.

`cd into/appropriate/dir`
`git clone --depth=1 git@github.com:libsdl-org/SDL.git`
`cd SDL`
`del build\CMakeCache.txt&rmdir /s/q build\CMakeFiles`
`cmake -B ./build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=on -DSDL_STATIC=ON -DSDL_SHARED=ON -DVIDEO_OPENGLES=0`
`cmake --build build --parallel`

After this, the build dir can be moved to sce/deps/SDL along with the includes folder. Only the .a file is necessary. It is possible to setup Cmake to automatically build & install SDL.

### SDL_ttf

`cd ../`
`git clone --depth=1 git@github.com:libsdl-org/SDL_ttf.git`
`cd SDL_ttf`
`del build\CMakeCache.txt&rmdir /s/q build\CMakeFiles`
`cmake -B ./build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=../SDL/build -DCMAKE_EXPORT_COMPILE_COMMANDS=on -DBUILD_SHARED_LIBS=OFF`
`cmake --build build --parallel`

After this, the build dir can be moved to sce/deps/SDL_ttf along with the includes folder. Only the .a file is necessary. It is possible to setup Cmake to automatically build & install SDL.

### Sce itself

`cd ../sce`
`mkdir build`
`del build\CMakeCache.txt&rmdir /s/q build\CMakeFiles`
`cmake -B ./build -G "MSYS Makefiles" -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=on DBUILD_SHARED_LIBS=ON`
`cmake --build build --parallel`
`.\build\sce.exe&echo %ERRORLEVEL%`

Exe-dir must contain FreeType.ttf.

## Run experimental test setup

(Tests are linked with SDL)
`copy /Y .\build\SDL3.dll .\build\test\ >NUL&copy /Y .\build\SDL3_ttf.dll .\build\test\ >NUL`
`ctest --test-dir .\build\test .\build\test\testproj.exe -V`

## Test font example
https://github.com/twardoch/test-fonts/blob/master/gx/SorcerySansGX-OFL/ttf/SorcerySansGX.ttf
