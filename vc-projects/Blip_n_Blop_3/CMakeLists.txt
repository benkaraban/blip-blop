cmake_minimum_required(VERSION 3.15)

project(blipblop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
find_library(SDL2_LIBRARIES SDL2)
find_library(SDL2MIXER_LIBRARIES SDL2_mixer)
find_path(SDL2_INCLUDE_DIRS SDL2/SDL.h)

aux_source_directory(. SRC)
aux_source_directory(menus MENUS_SRC)
# Note: an "Engine" source subdirectory was referenced here previously, but it
# does not exist anywhere in this repository (verified during Etap 1 audit).
# It has been removed as dead configuration. If an Engine/ split is introduced
# in a later stage, re-add aux_source_directory(Engine ENGINE_SRC) then.

if(WIN32)
    # WIN32 here tells add_executable to link as a GUI (WinMain) subsystem
    # app instead of a console app. This flag was previously (incorrectly)
    # placed in the else() branch below, which meant a Windows build linked
    # as a console app and showed a console window behind the game. Fixed as
    # part of the Etap 1 audit; no gameplay or architecture change.
    #
    # Consequence of a real WIN32 subsystem target on MSVC: the linker's
    # default entry point becomes WinMainCRTStartup, which expects a
    # WinMain(). This project has a plain int main(argc, argv) (see
    # blip_n_blop_3.cpp) and relies on neither SDL_MAIN_HANDLED nor an
    # observed rename of main to SDL_main by SDL2's headers in this
    # toolchain, so linking SDL2main here previously caused a duplicate
    # `main` (LNK2005) plus an unresolved `SDL_main` (LNK2019) - confirmed
    # via an actual CI run. Rather than depend on that header/macro
    # behavior, tell the MSVC linker to use the normal C runtime startup
    # (mainCRTStartup, which calls main()) instead of the WinMain-based one.
    # This keeps the GUI subsystem (still set via /SUBSYSTEM:WINDOWS by
    # WIN32 above - that's what actually suppresses the console window,
    # independent of the entry point) while requiring no SDL2main link and
    # no source changes.
    if(MSVC)
        set(BLIPBLOP_WIN32_LINK_FLAGS "/ENTRY:mainCRTStartup")
    endif()

    add_executable(blipblop WIN32 ${SRC} ${MENUS_SRC})
    target_link_libraries(blipblop PUBLIC ${SDL2_LIBRARIES})
    if(BLIPBLOP_WIN32_LINK_FLAGS)
        set_target_properties(blipblop PROPERTIES LINK_FLAGS "${BLIPBLOP_WIN32_LINK_FLAGS}")
    endif()

    target_link_libraries(blipblop PUBLIC ${SDL2MIXER_LIBRARIES})

    target_include_directories(blipblop SYSTEM PUBLIC ${SDL2_INCLUDE_DIRS})

    set(CMAKE_INSTALL_UCRT_LIBRARIES true)
    include(InstallRequiredSystemLibraries)
    install(DIRECTORY
        "${CMAKE_CURRENT_BINARY_DIR}/\${CMAKE_INSTALL_CONFIG_NAME}/"
        DESTINATION .
        FILES_MATCHING PATTERN "*.dll")
else()
    add_executable(blipblop ${SRC} ${MENUS_SRC})
    target_link_libraries(blipblop SDL2)
    target_link_libraries(blipblop SDL2_mixer)
endif()

install(DIRECTORY ./data DESTINATION .)
install(TARGETS blipblop RUNTIME DESTINATION .)

set(CPACK_PACKAGE_NAME "BlipnBlop")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Blip & Blop revamped")
set(CPACK_PACKAGE_VENDOR "Loaded Studios")
set(CPACK_DEBIAN_PACKAGE_NAME "blipnblop")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libSDL2, libSD2-mixer")
set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Blip & Blop revamped")
set(CPACK_PACKAGE_EXECUTABLES "blipblop" "BlipnBlop")

if(WIN32)
    set(CPACK_NSIS_DISPLAY_NAME "Blip & Blop")
    set(CPACK_NSIS_EXECUTABLES_DIRECTORY ".")
endif()

include(CPack)

