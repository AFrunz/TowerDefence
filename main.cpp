#include <iostream>
#include <vector>



#include "headers/TowerDefence.h"


//const char* castleFileName = "settingFiles/castle.txt";
//const char* mapFileName = "settingFiles/map.txt";
//const char* lairFileName = "settingFiles/lair.txt";
const std::string castleFileName = "/mnt/c/Users/frunz/Desktop/c_or_c++/TowerDefence/settingFiles/castle.txt";
const std::string mapFileName = "/mnt/c/Users/frunz/Desktop/c_or_c++/TowerDefence/settingFiles/map.txt";
const std::string lairFileName = "/mnt/c/Users/frunz/Desktop/c_or_c++/TowerDefence/settingFiles/lair.txt";


int main() {
    std::ifstream lairStream(lairFileName);
    std::ifstream castleStream(castleFileName);
    std::ifstream mapStream(mapFileName);

    TowerDefence td;
    td.loadMap(mapStream, castleStream, lairStream);
    td.startGame();
    return 0;
}
