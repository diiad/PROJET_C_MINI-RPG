cmake_minimum_required(VERSION 3.16)
project(RPG_C C)

# Standard C
set(CMAKE_C_STANDARD 11)

# Dossier include (Tes headers SDL sont dans include/SDL2)
if(APPLE)
    include_directories(${CMAKE_SOURCE_DIR}/include/macos)
endif()

if(WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/include/windows)
endif()

if(UNIX AND NOT APPLE)
    include_directories(${CMAKE_SOURCE_DIR}/include/linux)
endif()

# Exécutable principal
add_executable(RPG_C
        src/main.c
        src/struct.c
        src/combat.c
        src/ui.c
        include/struct.h
        include/ui.h
)

# OS detection

if(APPLE)
    message(STATUS "Building on MacOS")

    target_link_libraries(RPG_C
            "-F${CMAKE_SOURCE_DIR}/lib/macos"
            "-framework SDL2"
    )

    set_target_properties(RPG_C PROPERTIES
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
endif()