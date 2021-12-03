#include <iostream>

#include "headers/TowerDefence.h"








int main() {
    double timeStart = clock();
    std::string dialogOptions = {"0. Quit\n1. Do iter\n2. Add Tower\n3. Add magic tower\n4. Upgrade Tower\n5. Add trap\n"};


    std::ifstream lairStream(lairFileName);
    std::ifstream castleStream(castleFileName);
    std::ifstream mapStream(mapFileName);
    TowerDefence td;

    td.loadMap(mapStream, castleStream, lairStream);

    int choice = -1;
    int flag = 1;
    td.print();
    std::cout << dialogOptions;
    std::cin >> choice;
    while (choice != 0){
        if (choice == 1){
            std::cout << td.getTime() << std::endl;
            flag = td.oneIter();

        }
        else if (choice == 2){
            int x, y;
            std::cout << "Enter x and y\n";
            std::cin >> x >> y;
            td.addBaseTower(x, y);
        }
        else if (choice == 3){
            int x, y;
            std::cout << "Enter type:\n1 - slowing\n2 - poisoning\n3 - debilitation\n";
            int type = 0;
            std::cin >> type;
            std::cout << "Enter x and y\n";
            std::cin >> x >> y;
            td.addMagicTower(x, y, type);
        }
        else if (choice == 4){
            int x, y;
            std::cout << "Enter x and y\n";
            std::cin >> x >> y;
            td.towerUp(x, y);
        }
        else if (choice == 5){
            int x, y;
            std::cout << "Enter type:\n1 - slowing\n2 - poisoning\n3 - debilitation\n";
            int type = 0;
            std::cin >> type;
            std::cout << "Enter x and y\n";
            std::cin >> x >> y;
            td.addTrap(x, y, type);
        }
        td.print();
        if (flag == 0) return 0;
        std::cout << dialogOptions;
        std::cin >> choice;
    }

//    td.startGame();
    std::cout << (clock() - timeStart) / CLOCKS_PER_SEC;
    return 0;
}

//int main(){
//    int *p = new int;
//    int a = (*(p + 1));
//
//}
