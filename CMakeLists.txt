cmake_minimum_required(VERSION 3.16)
project(RPG_C C)

# Standard C
set(CMAKE_C_STANDARD 11)

# Dossiers include du projet et SDL
include_directories(${CMAKE_SOURCE_DIR}/include)
if(APPLE)
    include_directories(${CMAKE_SOURCE_DIR}/include/macos)
endif()

if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/include/windows)
endif()

if(UNIX AND NOT APPLE)
    include_directories(${CMAKE_SOURCE_DIR}/include/linux)
endif()

# Exécutable principal (jeu)
add_executable(RPG_C
        src/main.c
        src/struct.c
        src/classes.c
        src/moves.c
        src/scores.c
        src/map.c
        src/jeu.c
        src/interface.c
        src/inputs.c
        src/logic.c
)

# Éditeur de carte (exécutable séparé)
add_executable(RPG_C_Editor
        src/map_editor.c
        include/map_editor.h
)

# Assure que quand on construit le jeu (RPG_C) via CLion/IDE, l'éditeur est
# construit aussi. Ainsi, l'exécutable RPG_C_Editor sera bien présent dans le
# dossier de build et pourra être lancé depuis le menu du jeu.
add_dependencies(RPG_C RPG_C_Editor)

# Place les exécutables dans le même dossier de build (robuste selon le générateur)
set_target_properties(RPG_C PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(RPG_C_Editor PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

# Multi-config (Xcode/Visual Studio) : assure la même sortie pour chaque config
foreach(OUTPUTCONFIG Debug Release RelWithDebInfo MinSizeRel)
    set_target_properties(RPG_C PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR})
    set_target_properties(RPG_C_Editor PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR})
endforeach()

# OS detection

if(APPLE)
    message(STATUS "Building on MacOS")

    target_link_libraries(RPG_C
            "-F${CMAKE_SOURCE_DIR}/lib/macos"
            "-framework SDL2"
    )

    target_link_libraries(RPG_C_Editor
            "-F${CMAKE_SOURCE_DIR}/lib/macos"
            "-framework SDL2"
    )

    set_target_properties(RPG_C PROPERTIES
            INSTALL_RPATH "${CMAKE_SOURCE_DIR}/lib/macos"
            BUILD_WITH_INSTALL_RPATH TRUE
    )
    set_target_properties(RPG_C_Editor PROPERTIES
            INSTALL_RPATH "${CMAKE_SOURCE_DIR}/lib/macos"
            BUILD_WITH_INSTALL_RPATH TRUE
    )
endif()

if(WIN32)
    message(STATUS "Building on Windows")

    target_link_libraries(RPG_C
            ${CMAKE_SOURCE_DIR}/lib/windows/SDL2.lib
            ${CMAKE_SOURCE_DIR}/lib/windows/SDL2main.lib
    )
    target_link_libraries(RPG_C_Editor
            ${CMAKE_SOURCE_DIR}/lib/windows/SDL2.lib
            ${CMAKE_SOURCE_DIR}/lib/windows/SDL2main.lib
    )
endif()

if(UNIX AND NOT APPLE)
    find_package(SDL2 REQUIRED)
    if(TARGET SDL2::SDL2)
        target_link_libraries(RPG_C SDL2::SDL2)
        target_link_libraries(RPG_C_Editor SDL2::SDL2)
    else()
        # Fallback au cas où l'alias n'existe pas
        target_link_libraries(RPG_C SDL2)
        target_link_libraries(RPG_C_Editor SDL2)
    endif()
endif()