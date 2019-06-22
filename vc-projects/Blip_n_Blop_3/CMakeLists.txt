cmake_minimum_required(VERSION 2.8)

project(blipblop)

include(FindPkgConfig)
pkg_search_module(sdl2 REQUIRED sdl2)
pkg_search_module(SDL2_mixer REQUIRED SDL2_mixer)

include_directories(Engine)
#include_directories(${SDL2_INCLUDE_DIRS})
#include_directories(${SDL2_mixer_INCLUDE_DIRS})

aux_source_directory(. SRC)
aux_source_directory(Engine ENGINE_SRC)
aux_source_directory(menus MENUS_SRC)

add_executable(blipblop ${SRC} ${ENGINE_SRC} ${MENUS_SRC})
target_link_libraries(blipblop ${SDL2_LIBRARIES})
target_link_libraries(blipblop ${SDL2_mixer_LIBRARIES})

