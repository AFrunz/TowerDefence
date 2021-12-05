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


    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
//  Инициализация окна
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TowerDefence", sf::Style::Default, settings);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);
// Загрузка карты
    TowerDefence td(window);
    gm::loadMap(td);

// Загрузка карты


    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code){
                        case sf::Keyboard::Enter: {
                            int status = td.oneIter();
                            if (!status) window.close();
                            break;
                        }
                        case sf::Keyboard::B: {
                            int x, y;
                            while (event.type != sf::Event::MouseButtonPressed) {
                                window.pollEvent(event);
                            }
                            x = (event.mouseButton.x - MAP_OFFSET_X) / (MAP_SIZE / td.getSize());
                            y = (event.mouseButton.y - MAP_OFFSET_Y) / (MAP_SIZE / td.getSize());
                            td.addBaseTower(x, y);
                            break;
                        }
                        case sf::Keyboard::M:{
                            while (event.type != sf::Event::KeyPressed ||
                                    (event.key.code != sf::Keyboard::Num1 &&
                                     event.key.code != sf::Keyboard::Num2 &&
                                     event.key.code != sf::Keyboard::Num3)){
                                window.pollEvent(event);
                            }
                            int type;
                            switch (event.key.code) {
                                case sf::Keyboard::Num1:{
                                    type = 1;
                                    break;
                                }
                                case sf::Keyboard::Num2:{
                                    type = 2;
                                    break;
                                }
                                default: {
                                type = 3;
                                }
                            }
                            int x, y;
                            while (event.type != sf::Event::MouseButtonPressed) {
                                window.pollEvent(event);
                            }
                            x = (event.mouseButton.x - MAP_OFFSET_X) / (MAP_SIZE / td.getSize());
                            y = (event.mouseButton.y - MAP_OFFSET_Y) / (MAP_SIZE / td.getSize());
                            td.addMagicTower(x, y, type);
                            break;
                        }
                        case sf::Keyboard::T:{
                            while (event.type != sf::Event::KeyPressed ||
                                   (event.key.code != sf::Keyboard::Num1 &&
                                    event.key.code != sf::Keyboard::Num2 &&
                                    event.key.code != sf::Keyboard::Num3)){
                                window.pollEvent(event);
                            }
                            int type;
                            switch (event.key.code) {
                                case sf::Keyboard::Num1:{
                                    type = 1;
                                    break;
                                }
                                case sf::Keyboard::Num2:{
                                    type = 2;
                                    break;
                                }
                                default: {
                                    type = 3;
                                }
                            }
                            int x, y;
                            while (event.type != sf::Event::MouseButtonPressed) {
                                window.pollEvent(event);
                            }
                            x = (event.mouseButton.x - MAP_OFFSET_X) / (MAP_SIZE / td.getSize());
                            y = (event.mouseButton.y - MAP_OFFSET_Y) / (MAP_SIZE / td.getSize());
                            td.addTrap(x, y, type);
                        }
                     break;
             }
                    break;
                case sf::Event::MouseButtonPressed:{
                    int x = (event.mouseButton.x - MAP_OFFSET_X) / (MAP_SIZE / td.getSize());
                    int y = (event.mouseButton.y - MAP_OFFSET_Y) / (MAP_SIZE / td.getSize());
                    td.towerUp(x, y);
                }
        }
//
//            if (event.type == sf::Event::MouseButtonPressed){
//                int status = td.oneIter();
//                if (!status) window.close();
//                std::cout << "Iter\n";
//            }

            window.display();
        }
    }


    return 0;
}
