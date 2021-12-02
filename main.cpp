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
    double timeStart = clock();

    std::ifstream lairStream(lairFileName);
    std::ifstream castleStream(castleFileName);
    std::ifstream mapStream(mapFileName);
    TowerDefence td;

    td.loadMap(mapStream, castleStream, lairStream);

    int choice = -1;
    int flag = 1;
    td.print();
    std::cout << "0.Quit\n1.Add Tower\n2.Upgrade Tower\n3.Do iter\n";
    std::cin >> choice;
    while (choice != 0 && flag != 0){
        if (choice == 1){
            int x, y;
            std::cout << "Enter x and y\n";
            std::cin >> x >> y;
            td.addTower(x, y);
        }
        else if (choice == 2){
            int x, y;
            std::cout << "Enter x and y\n";
            std::cin >> x >> y;
            td.towerUp(x, y);
        }
        else if (choice == 3){
            std::cout << td.getTime() << std::endl;
            flag = td.oneIter();
        }
        td.print();
        std::cout << "0.Quit\n1.Add Tower\n2.Upgrade Tower\n3.Do iter\n";
        std::cin >> choice;
    }
//    td.startGame();
    std::cout << (clock() - timeStart) / CLOCKS_PER_SEC;
    return 0;
}
