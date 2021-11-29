project(Google_tests)

if(WIN32)
    set(SOURCE "C:\\Users\\frunz\\Desktop\\c_or_c++\\TowerDefenceV2")
else()
    set(SOURCE "/mnt/c/Users/frunz/Desktop/c_or_c++/TowerDefenceV2/")
endif()
message(${SOURCE})
# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${SOURCE}/headers)
message(${gtest_SOURCE_DIR})
# 'Google_Tests_run' is the target name
add_executable(Google_Tests_run tests.cpp ${SOURCE}/Castle.cpp ${SOURCE}/Enemy.cpp ${SOURCE}/Spell.cpp ${SOURCE}/Lair.cpp
        ${SOURCE}/Trap.cpp ${SOURCE}/Tower.cpp ${SOURCE}/TowerDefence.cpp ${SOURCE}/Landscape.cpp)
#${SOURCE}/lab3/headers/sequence.hpp ${SOURCE}/lab3/sequence.cpp
target_link_libraries(Google_Tests_run gtest gtest_main)