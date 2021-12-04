#include "headers/TowerDefence.h"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace gm {
    void loadMap(TowerDefence& td){
        std::ifstream lairStream(lairFileName);
        std::ifstream castleStream(castleFileName);
        std::ifstream mapStream(mapFileName);
        td.loadMap(mapStream, castleStream, lairStream);
    }

}

namespace ts{
    void backgroundTextureLoad(sf::RenderWindow& window){
        sf::Sprite sprite;
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("bin/content/textures/Background.jpg")) {
            std::cout << "Error\n";
        }
        sprite.setTexture(backgroundTexture);
    }
    void mapTextureLoad(sf::RenderWindow& window, TowerDefence& td){
        Landscape landscape = td.getLandscapeCopy();



    }
    void




}





int main(){
    double timeStart = clock();
//    std::string dialogOptions = {"0. Quit\n1. Do iter\n2. Add Tower\n3. Add magic tower\n4. Upgrade Tower\n5. Add trap\n"};
// Загрузка карты
    TowerDefence td;
    gm::loadMap(td);


//  Инициализация окна
    sf::RenderWindow window(sf::VideoMode(800, 600), "TowerDefence");
    window.setVerticalSyncEnabled(true);


    while (window.isOpen()) {
        sf::Event event;
        ts::backgroundTextureLoad(window);
        ts::mapTextureLoad(window, td);


        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }




            window.display();
        }
    }


    return 0;
}
