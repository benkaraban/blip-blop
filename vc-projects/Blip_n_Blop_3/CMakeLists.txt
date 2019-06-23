cmake_minimum_required(VERSION 3.1)

project(blipblop)

find_package(SDL2 REQUIRED)
find_path(SDL2_INCLUDE_DIRS SDL2/SDL.h)

#include_directories(${SDL2_INCLUDE_DIRS})
#include_directories(${SDL2_mixer_INCLUDE_DIRS})

aux_source_directory(. SRC)
aux_source_directory(Engine ENGINE_SRC)
aux_source_directory(menus MENUS_SRC)

add_executable(blipblop ${SRC} ${ENGINE_SRC} ${MENUS_SRC})
target_link_libraries(blipblop SDL2)
target_link_libraries(blipblop SDL2_mixer)
target_include_directories(blipblop SYSTEM PUBLIC ${SDL2_INCLUDE_DIRS})

install(TARGETS blipblop DESTINATION blipblop)
include(CPack)

