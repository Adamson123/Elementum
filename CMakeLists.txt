cmake_minimum_required(VERSION 3.16)
project(SDL-Text-Editor)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(app ${SRC_FILES})

target_include_directories(app PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(app ${SDL2_LIBRARIES})