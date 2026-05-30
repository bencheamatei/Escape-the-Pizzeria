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

FetchContent_Declare(
        nlohmann_json
        URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)

FetchContent_MakeAvailable(nlohmann_json)

find_package(Threads REQUIRED)
if(APPLE)
elseif(UNIX)
    find_package(X11)
endif()

add_executable(${MAIN_EXECUTABLE_NAME}
        main.cpp
        include/items/item.h
        src/items/item.cpp
        include/items/topping.h
        src/items/topping.cpp
        include/inventory.h
        src/inventory.cpp
        include/inventorySlot.h
        src/inventorySlot.cpp
        include/player.h
        src/player.cpp
        include/items/pizza.h
        src/items/pizza.cpp
        include/exceptions.h
        src/exceptions.cpp
        include/items/dough.h
        src/items/dough.cpp

        generated/src/Helper.cpp
        ResourceManager.cpp
        ResourceManager.hpp
        src/scenes/scene.cpp
        include/scenes/scene.h
        src/game.cpp
        include/game.h
        src/scenes/menu_scene.cpp
        include/scenes/menu_scene.h
        src/room.cpp
        include/room.h
        src/renders/player_render.cpp
        include/renders/player_render.h
        src/inventory_ui.cpp
        include/inventory_ui.h
        src/scenes/game_scene.cpp
        include/scenes/game_scene.h
        src/scenes/pause_scene.cpp
        include/scenes/pause_scene.h
        src/items/backpack.cpp
        include/items/backpack.h
        src/status_effect.cpp
        include/status_effect.h
        src/food_poisoning.cpp
        include/food_poisoning.h
        src/items/soda.cpp
        include/items/soda.h
        src/animatronics/animatronic.cpp
        include/animatronic/animatronic.h
        src/animatronics/freddy.cpp
        include/animatronic/freddy.h
        src/renders/animatronic_render.cpp
        include/renders/animatronic_render.h
        src/animatronics/animatronic_ai.cpp
        include/animatronic/animatronic_ai.h
        src/game_states/game_state.cpp
        include/game_states/game_state.h
        src/game_states/playing_state.cpp
        include/game_states/playing_state.h
        src/game_states/death_state.cpp
        include/game_states/death_state.h
        src/game_states/respawn_state.cpp
        include/game_states/respawn_state.h
        src/animatronics/foxy.cpp
        include/animatronic/foxy.h
        src/animatronic_factory.cpp
        include/animatronic_factory.h
        src/animatronics/chica.cpp
        include/animatronic/chica.h
        src/animatronics/nightmare.cpp
        include/animatronic/nightmare.h
)

set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

target_include_directories(${MAIN_EXECUTABLE_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE generated/include)
target_include_directories(${MAIN_EXECUTABLE_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
target_link_directories(${MAIN_EXECUTABLE_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE sfml-graphics sfml-window sfml-system Threads::Threads nlohmann_json::nlohmann_json)

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