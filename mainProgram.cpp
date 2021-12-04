#include "headers/TowerDefence.h"
#include <SFML/Graphics.hpp>
#include <iostream>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;


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
        window.draw(sprite);
    }

    sf::Sprite getForestTexture();
    sf::Sprite getLairTexture();
    sf::Sprite getCastleTexture();


    void mapTextureLoad(sf::RenderWindow& window, TowerDefence& td){
        sf::Sprite sprite;
        sf::RectangleShape borderOfMap(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2));
        borderOfMap.move(WINDOW_WIDTH * 0.07, WINDOW_HEIGHT * 0.2);

        Landscape landscape = td.getLandscapeCopy();
        for (auto it = landscape.begin(); it != landscape.end(); it++){
            if ((*it).type == forest){
                if ((*it).building){
                    if ((*it).building->getType() == castle_){
                        getCastleTexture();
                        //
                    }
                    else {
                        getLairTexture();
                        //

                    }
                }
                else {
                    getForestTexture();
                }
            }
            else if ((*it).type == road){
                getRoadTexture();
                //
            }
            else if ((*))


        }



        window.draw(borderOfMap);
    }

}





int main(){
    double timeStart = clock();
//    std::string dialogOptions = {"0. Quit\n1. Do iter\n2. Add Tower\n3. Add magic tower\n4. Upgrade Tower\n5. Add trap\n"};
// Загрузка карты
    TowerDefence td;
    gm::loadMap(td);


//  Инициализация окна
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TowerDefence");
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
