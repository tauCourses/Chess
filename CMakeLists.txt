cmake_minimum_required(VERSION 3.8)
project(Chess)

set(CMAKE_C_STANDARD 99)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${Chess_SOURCE_DIR}/cmake")
set(SDL2_DIR "C:\\SDL2\\SDL2-2.0.5\\x86_64-w64-mingw32")
set(SDL2_INCLUDE_DIR "C:\\SDL2\\SDL2-2.0.5\\x86_64-w64-mingw32\\include\\SDL2")
set(SDL2_IMAGE_INCLUDE_DIR "C:\\SDL2\\SDL2-2.0.5\\x86_64-w64-mingw32\\include\\SDL2")
set(SDL2_LIB_DIR "C:\\SDL2\\SDL2-2.0.5\\x86_64-w64-mingw32\\lib")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR} ${Chess_SOURCE_DIR}/source/headers)

set(SOURCE_FILES main.c MainWindow.h MainWindow.c GUIManager.h GUIManager.c Button.h Button.c
        LoadGameWindow.c LoadGameWindow.h ModeWindow.h ModeWindow.c DifficultyWindow.h DifficultyWindow.c
        ColorWindow.h ColorWindow.c GameWindow.h GameWindow.c BoardLayout.h BoardLayout.c
        console.h console.c game.h game.c gameAux.h gameAux.c genericArrayList.h genericArrayList.c
        Infrastructure.h SPArrayList.h SPArrayList.c gameTests.h gameTests.c GameLayout.c GameLayout.h
        StatesStack.h StatesStack.c Storage.h Storage.c)
add_executable(Chess ${SOURCE_FILES})

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_image_LIBRARIES})