cmake_minimum_required(VERSION 3.16)
project(TowerDefence)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(Google_tests)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(TowerDefence mainProgram.cpp Landscape.cpp Lair.cpp Castle.cpp Spell.cpp Tower.cpp TowerDefence.cpp
        headers/TowerDefence.h Enemy.cpp Trap.cpp
        headers/settings.h headers/TextureLoader.hpp)

target_link_libraries(TowerDefence sfml-graphics sfml-audio)
#add_executable(TowerDefence main.cpp)

