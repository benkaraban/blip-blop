cmake_minimum_required(VERSION 3.1)

project(blipblop)

find_package(SDL2 REQUIRED)
find_library(SDL2_LIBRARIES SDL2)
find_library(SDL2MIXER_LIBRARIES SDL2_mixer)
find_path(SDL2_INCLUDE_DIRS SDL2/SDL.h)

aux_source_directory(. SRC)
aux_source_directory(Engine ENGINE_SRC)
aux_source_directory(menus MENUS_SRC)

if(WIN32)
    add_executable(blipblop ${SRC} ${ENGINE_SRC} ${MENUS_SRC})
    target_link_libraries(blipblop PUBLIC ${SDL2_LIBRARIES})
    target_link_libraries(blipblop PUBLIC ${SDL2MIXER_LIBRARIES})
    target_include_directories(blipblop SYSTEM PUBLIC ${SDL2_INCLUDE_DIRS})

    set(CMAKE_INSTALL_UCRT_LIBRARIES true)
    include(InstallRequiredSystemLibraries)
    install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/\${CMAKE_INSTALL_CONFIG_NAME}/" DESTINATION bin FILES_MATCHING PATTERN "*.dll")
else()
    add_executable(blipblop WIN32 ${SRC} ${ENGINE_SRC} ${MENUS_SRC})
    target_link_libraries(blipblop SDL2)
    target_link_libraries(blipblop SDL2_mixer)
endif()

install(DIRECTORY ./data DESTINATION bin)
install(TARGETS blipblop RUNTIME DESTINATION bin)
include(CPack)

