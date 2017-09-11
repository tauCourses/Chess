cmake_minimum_required(VERSION 3.8)
project(Chess)

set(SDL2_INCLUDE_DIR /usr/include/SDL2)
set(SDL2_LIBRARY /usr/lib/x86_64-linux-gnu//libSDL2.so)
set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c MainWindow.h MainWindow.c GUIManager.h GUIManager.c Button.h Button.c
        LoadGameWindow.c LoadGameWindow.h ModeWindow.h ModeWindow.c DifficultyWindow.h DifficultyWindow.c
        ColorWindow.h ColorWindow.c GameWindow.h GameWindow.c BoardLayout.h BoardLayout.c
        console.h console.c game.h game.c gameAux.h gameAux.c genericArrayList.h genericArrayList.c
        Infrastructure.h SPArrayList.h SPArrayList.c gameTests.h gameTests.c GameLayout.c GameLayout.h
        StatesStack.h StatesStack.c)
add_executable(Chess ${SOURCE_FILES})


find_package(PkgConfig)
find_package(SDL2 REQUIRED)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_image_LIBRARIES})