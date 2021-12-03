cmake_minimum_required(VERSION 3.16)
project(TowerDefence)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(Google_tests)


add_executable(TowerDefence main.cpp Landscape.cpp Lair.cpp Castle.cpp Spell.cpp Tower.cpp TowerDefence.cpp
        headers/TowerDefence.h Enemy.cpp headers/list.hpp Trap.cpp
        mainProgram.cpp headers/settings.h)
#add_executable(TowerDefence main.cpp)

