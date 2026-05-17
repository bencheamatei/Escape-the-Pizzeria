cmake_minimum_required(VERSION 3.26)

set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")

project(${MAIN_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)

include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(WARNINGS_AS_ERRORS OFF)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2.6.2
        GIT_SHALLOW    1
)

FetchContent_MakeAvailable(SFML)

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

add_executable(${MAIN_EXECUTABLE_NAME}
        main.cpp
        include/item.h
        src/item.cpp
        include/topping.h
        src/topping.cpp
        include/inventory.h
        src/inventory.cpp
        include/inventorySlot.h
        src/inventorySlot.cpp
        include/player.h
        src/player.cpp
        include/pizza.h
        src/pizza.cpp
        include/exceptions.h
        src/exceptions.cpp
        include/dough.h
        src/dough.cpp

        generated/src/Helper.cpp
        ResourceManager.cpp
        ResourceManager.hpp
        src/scene.cpp
        include/scene.h
        src/game.cpp
        include/game.h
        src/menu_scene.cpp
        include/menu_scene.h
        src/room.cpp
        include/room.h
        src/player_render.cpp
        include/player_render.h
        src/inventory_ui.cpp
        include/inventory_ui.h
        src/game_scene.cpp
        include/game_scene.h
        src/pause_scene.cpp
        include/pause_scene.h
        src/backpack.cpp
        include/backpack.h
        src/status_effect.cpp
        include/status_effect.h
        src/food_poisoning.cpp
        include/food_poisoning.h
        src/soda.cpp
        include/soda.h
        src/animatronic.cpp
        include/animatronic.h
        src/freddy.cpp
        include/freddy.h
        src/animatronic_render.cpp
        include/animatronic_render.h
        src/animatronic_ai.cpp
        include/animatronic_ai.h
)

set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

target_include_directories(${MAIN_EXECUTABLE_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE generated/include)
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_link_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE sfml-graphics sfml-window sfml-system Threads::Threads)

if(APPLE)
elseif(UNIX)
    target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE X11)
endif()

install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

if (WIN32 AND SFML_BUILD_AUDIO)
    add_custom_command(TARGET ${MAIN_EXECUTABLE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SFML_SOURCE_DIR}/extlibs/bin/x64/openal32.dll
            $<TARGET_FILE_DIR:${MAIN_EXECUTABLE_NAME}>
    )
endif()

copy_files(FILES tastatura.txt DIRECTORY assets images fonts COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})