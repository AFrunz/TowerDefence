#include "headers/TowerDefence.h"
#include <iostream>
//#include "headers/TextureLoader.hpp"



namespace gm {
    void loadMap(TowerDefence& td){
        std::ifstream lairStream(lairFileName);
        std::ifstream castleStream(castleFileName);
        std::ifstream mapStream(mapFileName);
        td.loadMap(mapStream, castleStream, lairStream);
    }

}






int main(){
    double timeStart = clock();
//    std::string dialogOptions = {"0. Quit\n1. Do iter\n2. Add Tower\n3. Add magic tower\n4. Upgrade Tower\n5. Add trap\n"};



//  Инициализация окна
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TowerDefence");
    window.setVerticalSyncEnabled(true);

// Загрузка карты
    TowerDefence td(window);
    gm::loadMap(td);

// Загрузка карты


    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed){
                int status = td.oneIter();
                if (!status) window.close();
                std::cout << "Iter\n";
            }
            window.display();
        }
    }


    return 0;
}
