cmake_minimum_required(VERSION 2.8)

project(blipblop)

include_directories(Engine)
aux_source_directory(. SRC)
add_executable(blipblop ${SRC})

add_custom_target(astyle COMMAND
    astyle --indent=tab --indent-preprocessor --style=kr
    --pad-oper --pad-header --unpad-paren -S -n
    --recursive ${CMAKE_SOURCE_DIR}"/*.cpp" ${CMAKE_SOURCE_DIR}"/*.h"
)
