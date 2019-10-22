cmake_minimum_required(VERSION 3.14)
project(GujarunSFML)

set(CMAKE_CXX_STANDARD 14)
set(SFML_INCLUDE_DIR "/usr/local/cellar/sfml/2.5.1/include")
set(SFML_LIBRARY_DIR "/usr/local/cellar/sfml/2.5.1/lib")
set(SFML_DIR "/usr/local/cellar/sfml/2.5.1/lib/cmake/SFML")
link_directories(${SFML_LIBRARY_DIR})
include_directories(${SFML_INCLUDE_DIR})
find_package(SFML 2.5.1 REQUIRED COMPONENTS system window graphics network audio)
if(SFML_FOUND)
        message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
        message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARY_DIR}")
endif()
add_executable(GujarunSFML main.cpp Game.cpp Game.h States/State.cpp States/State.h States/GameState.cpp States/GameState.h
        Entities/Entity.cpp Entities/Entity.h States/mainmenuState.cpp States/mainmenuState.h GUI.cpp GUI.h Entities/Player.cpp Entities/Player.h
        Components/MovementComponent.cpp Components/MovementComponent.h Components/AnimationComponent.cpp Components/AnimationComponent.h States/EditorState.cpp States/EditorState.h Components/HitboxComponent.cpp Components/HitboxComponent.h Tile.cpp Tile.h GUI/PauseMenu.cpp GUI/PauseMenu.h States/SettingsState.cpp States/SettingsState.h Map/TileMap.cpp Map/TileMap.h Precom.cpp Precom.h GraphicsSettings.cpp GraphicsSettings.h Sound/Sound.cpp Sound/Sound.h)
target_link_libraries(GujarunSFML sfml-graphics sfml-network sfml-window sfml-audio sfml-system)