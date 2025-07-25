cmake_minimum_required(VERSION 3.10)
project(TetrisProyecto LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ruta al directorio de las DLLs (ajústalo si cambia)
set(SFML_BIN_DIR "${CMAKE_SOURCE_DIR}/SFML-3.0.0/bin")
set(MINGW_BIN_DIR "${CMAKE_SOURCE_DIR}/mingw64/bin")

find_package(SFML 3.0 COMPONENTS System Window Graphics REQUIRED)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(SFML_SUFFIX "-d")
else()
    set(SFML_SUFFIX "")
endif()

find_package(SFML 3.0 COMPONENTS System Window Graphics REQUIRED)

# Luego usa ${SFML_SUFFIX} cuando copies los DLLs



add_executable(tetris
        src/main.cpp
)


target_link_libraries(tetris PRIVATE
        SFML::System
        SFML::Window
        SFML::Graphics
)

file(GLOB SFML_DLLS
        "${SFML_BIN_DIR}/sfml-system-d-3.dll"
        "${SFML_BIN_DIR}/sfml-window-d-3.dll"
        "${SFML_BIN_DIR}/sfml-graphics-d-3.dll"
        "${MINGW_BIN_DIR}/libwinpthread-1.dll"
        "${MINGW_BIN_DIR}/libgcc_s_seh-1.dll"
        "${MINGW_BIN_DIR}/libstdc++-6.dll"
)
# Copiar carpeta res completa al directorio del ejecutable tras build
add_custom_command(TARGET tetris POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res"
        $<TARGET_FILE_DIR:tetris>/res
)

foreach(dll ${SFML_DLLS})
    add_custom_command(TARGET tetris POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${dll}"
            $<TARGET_FILE_DIR:tetris>
    )
endforeach()
