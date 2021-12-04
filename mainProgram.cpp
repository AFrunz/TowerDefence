#include "headers/TowerDefence.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>

const float WINDOW_WIDTH = 800;
const float WINDOW_HEIGHT = 600;

//const float WINDOW_WIDTH = 1920;
//const float WINDOW_HEIGHT = 1080;

const float MAP_OFFSET_X = WINDOW_WIDTH * 0.07;
const float MAP_OFFSET_Y = WINDOW_HEIGHT * 0.2;
const float MAP_SIZE = WINDOW_HEIGHT / 2;
//const float MAP_HEIGHT = WINDOW_WIDTH / 2;


namespace gm {
    void loadMap(TowerDefence& td){
        std::ifstream lairStream(lairFileName);
        std::ifstream castleStream(castleFileName);
        std::ifstream mapStream(mapFileName);
        td.loadMap(mapStream, castleStream, lairStream);
    }

}

class TextureLoader{
public:
    std::map<std::string, sf::Texture> textures;
    std::list<sf::Sprite> sprites;

    void backgroundTextureDraw(sf::RenderWindow& window){
        sf::Sprite sprite;
        sf::Texture backgroundTexture;
        backgroundTexture.loadFromFile("bin/content/textures/Background.jpg");
        textures["background"] = backgroundTexture;
        float scaleX = (WINDOW_WIDTH) / backgroundTexture.getSize().x;
        float scaleY = (WINDOW_HEIGHT) / backgroundTexture.getSize().y;
        std::cout << backgroundTexture.getSize().x << backgroundTexture.getSize().y << scaleX << scaleY;
        sprite.setScale(scaleX, scaleY);
        sprite.setTexture(textures["background"]);
        sprites.push_back(sprite);
        window.draw(sprite);
    }

    sf::Sprite getForestTexture(int x, int y, int size){
        sf::Sprite forestSprite;
        sf::Texture forestTexture;
        forestTexture.loadFromFile("bin/content/textures/Forest.png");
        textures["forest"] = forestTexture;
        forestSprite.setTexture(textures["forest"]);
        float scaleX = (MAP_SIZE / size) / forestTexture.getSize().x;
        float scaleY = (MAP_SIZE / size) / forestTexture.getSize().y;
        forestSprite.setScale(scaleX, scaleY);
        int newX = MAP_OFFSET_X + x *  (MAP_SIZE / size);
        int newY = MAP_OFFSET_Y + y * (MAP_SIZE / size);
        forestSprite.setPosition(newX, newY);
//        window.draw(forestSprite);
        return forestSprite;
    }
    sf::Sprite getLairTexture(int x, int y, int size){
        sf::Sprite lairSprite;
        sf::Texture lairTexture;
        lairTexture.loadFromFile("bin/content/textures/Lair.png");
        textures["lair"] = lairTexture;
        lairSprite.setTexture(textures["lair"]);
        float scaleX = (MAP_SIZE / size) / lairTexture.getSize().x;
        float scaleY = (MAP_SIZE / size) / lairTexture.getSize().y;
        lairSprite.setScale(scaleX, scaleY);
        int newX = MAP_OFFSET_X + x *  (MAP_SIZE / size);
        int newY = MAP_OFFSET_Y + y * (MAP_SIZE / size);
        lairSprite.setPosition(newX, newY);
//        window.draw(forestSprite);
        return lairSprite;

    }
    sf::Sprite getCastleTexture(int x, int y, int size){
        sf::Sprite castleSprite;
        sf::Texture castleTexture;
        castleTexture.loadFromFile("bin/content/textures/Castle.jpg");
        textures["castle"] = castleTexture;
        castleSprite.setTexture(textures["castle"]);
        float scaleX = (MAP_SIZE / size) / castleTexture.getSize().x;
        float scaleY = (MAP_SIZE / size) / castleTexture.getSize().y;
        castleSprite.setScale(scaleX, scaleY);
        int newX = MAP_OFFSET_X + x *  (MAP_SIZE / size);
        int newY = MAP_OFFSET_Y + y * (MAP_SIZE / size);
        castleSprite.setPosition(newX, newY);
//        window.draw(forestSprite);
        return castleSprite;
    }

    sf::Sprite getRoadTexture(int x, int y, int size){
        sf::Sprite roadSprite;
        sf::Texture roadTexture;
        roadTexture.loadFromFile("bin/content/textures/Road.jpg");
        textures["road"] = roadTexture;
        roadSprite.setTexture(textures["road"]);
        float scaleX = (MAP_SIZE / size) / roadTexture.getSize().x;
        float scaleY = (MAP_SIZE / size) / roadTexture.getSize().y;
        roadSprite.setScale(scaleX, scaleY);
        int newX = MAP_OFFSET_X + x *  (MAP_SIZE / size);
        int newY = MAP_OFFSET_Y + y * (MAP_SIZE / size);
        roadSprite.setPosition(newX, newY);
//        window.draw(forestSprite);
        return roadSprite;
    }
    sf::Sprite getFieldTexture(int x, int y, int size){
        sf::Sprite fieldSprite;
        sf::Texture fieldTexture;
        fieldTexture.loadFromFile("bin/content/textures/Field.jpg");
        textures["field"] = fieldTexture;
        fieldSprite.setTexture(textures["field"]);
        float scaleX = (MAP_SIZE / size) / fieldTexture.getSize().x;
        float scaleY = (MAP_SIZE / size) / fieldTexture.getSize().y;
        fieldSprite.setScale(scaleX, scaleY);
        int newX = MAP_OFFSET_X + x *  (MAP_SIZE / size);
        int newY = MAP_OFFSET_Y + y * (MAP_SIZE / size);
        fieldSprite.setPosition(newX, newY);
//        window.draw(forestSprite);
        return fieldSprite;


    }

    void mapTextureInitialDraw(sf::RenderWindow& window, TowerDefence& td){
        sf::Sprite sprite;
        sf::RectangleShape borderOfMap(sf::Vector2f(MAP_SIZE, MAP_SIZE));
        borderOfMap.move(MAP_OFFSET_X, MAP_OFFSET_Y);
        window.draw(borderOfMap);
//        Landscape landscape = td.getLandscapeCopy();
//        auto it1 = landscape.begin();
//        auto it2 = landscape.end();
        for (auto it = td.begin(); it != td.end(); it++){
            if ((*it).type == forest){
                if ((*it).building){
                    if ((*it).building->getType() == castle_){
                        sf::Sprite castleSprite = getCastleTexture(it.getX(), it.getY(), it.getSize());
                        window.draw(castleSprite);
                        //
                    }
                    else {
                        sf::Sprite lairSprite = getLairTexture(it.getX(), it.getY(), it.getSize());
                        window.draw(lairSprite);

                    }
                }
                else {
                    sf::Sprite forestSprite = getForestTexture(it.getX(), it.getY(), it.getSize());

                    window.draw(forestSprite);
                }
            }
            else if ((*it).type == road){
                sf::Sprite roadSprite = getRoadTexture(it.getX(), it.getY(), it.getSize());
                window.draw(roadSprite);
                //
            }
            else if ((*it).type == field){
                sf::Sprite fieldSprite = getFieldTexture(it.getX(), it.getY(), it.getSize());
                window.draw(fieldSprite);
                //
            }
        }




    }



};










int main(){
    double timeStart = clock();
//    std::string dialogOptions = {"0. Quit\n1. Do iter\n2. Add Tower\n3. Add magic tower\n4. Upgrade Tower\n5. Add trap\n"};
// Загрузка карты
    TowerDefence td;
    gm::loadMap(td);


//  Инициализация окна
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "TowerDefence");
    window.setVerticalSyncEnabled(true);
    TextureLoader tl;

// Загрузка карты
    tl.backgroundTextureDraw(window);
    tl.mapTextureInitialDraw(window, td);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }




            window.display();
        }
    }


    return 0;
}
