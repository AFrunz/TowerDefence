#ifndef TOWERDEFENCE_TEXTURELOADER_HPP
#define TOWERDEFENCE_TEXTURELOADER_HPP
#include <map>
#include "settings.h"
#include <SFML/Graphics.hpp>
#include "Landscape.hpp"
#include <cmath>

class TextureLoader{
private:
    sf::RenderWindow* window;

public:
    TextureLoader(sf::RenderWindow* window_):window(window_){};
    sf::RenderWindow* getWindow() const{return window;};

    std::map<std::string, sf::Texture> textures;
    std::list<sf::Sprite> sprites;
    void backgroundTextureDraw(){
        sf::Sprite sprite;
        sf::Texture backgroundTexture;
        backgroundTexture.loadFromFile("bin/content/textures/Background.jpg");
        textures["background"] = backgroundTexture;
        float scaleX = (WINDOW_WIDTH) / backgroundTexture.getSize().x;
        float scaleY = (WINDOW_HEIGHT) / backgroundTexture.getSize().y;
        std::cout << backgroundTexture.getSize().x << backgroundTexture.getSize().y << scaleX << scaleY;
        sprite.setScale(scaleX, scaleY);
        sprite.setTexture(textures["background"]);
        sprites.push_front(sprite);
        window->draw(sprite);
    }

    void deleteTrapSprite(int x, int y, int size){
        for (auto sprite = std::prev(sprites.end()); sprite != sprites.begin(); sprite--){
            std:: cout << sprite->getPosition().x << "\n" << sprite->getPosition().y << "\n";
            int tX = round((sprite->getPosition().x - MAP_OFFSET_X) / (MAP_SIZE / size));
            int tY = round((sprite->getPosition().y - MAP_OFFSET_Y) / (MAP_SIZE / size));
            if (y == tX && x == tY){
                sprites.erase(sprite);
                return;
            }
        }
    }

    void addInterfaceTexture(){
        sf::Sprite sprite;
        sf::Texture interfaceTexture;
        interfaceTexture.loadFromFile("bin/content/textures/Interface1.png");
        textures["interface"] = interfaceTexture;
        float scaleX = (WINDOW_WIDTH / 2) / interfaceTexture.getSize().x;
        float scaleY = (WINDOW_HEIGHT / 3 * 2) / interfaceTexture.getSize().y;
        std::cout << interfaceTexture.getSize().x << interfaceTexture.getSize().y << scaleX << scaleY;
        sprite.setScale(scaleX, scaleY);
        sprite.setTexture(textures["interface"]);
        sprite.setPosition(INTERFACE_OFFSET_X, INTERFACE_OFFSET_Y);
        sprites.push_back(sprite);
    }
    void addTimer(){
        sf::Font font;
        font.loadFromFile("bin/content/fonts/arialmt.ttf");
        sf::Text timer("Время: ", font, 20);
        timer.setFillColor(sf::Color::Black);
        timer.setPosition(TIMER_OFFSET_X, TIMER_OFFSET_Y);
        window->draw(timer);
    }
    sf::Sprite addForestTexture(int x, int y, int size){
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
        sprites.push_back(forestSprite);
//        window.draw(forestSprite);
        return forestSprite;
    }
    sf::Sprite addLairTexture(int x, int y, int size){
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
        sprites.push_back(lairSprite);
//        window.draw(forestSprite);
        return lairSprite;

    }
    sf::Sprite addCastleTexture(int x, int y, int size){
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
        sprites.push_back(castleSprite);
//        window.draw(forestSprite);
        return castleSprite;
    }
    sf::Sprite addRoadTexture(int x, int y, int size){
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
        sprites.push_back(roadSprite);
        return roadSprite;
    }
    sf::Sprite addFieldTexture(int x, int y, int size){
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
        sprites.push_back(fieldSprite);
//        window.draw(forestSprite);
        return fieldSprite;
    }
    sf::Sprite addTowerTexture(int x, int y, int size, int type){
        sf::Sprite towerSprite;
        sf::Texture towerTexture;
        if (type == 1){
            towerTexture.loadFromFile("bin/content/textures/BaseTower.png");
            textures["baseTower"] = towerTexture;
            towerSprite.setTexture(textures["baseTower"]);
        }
        else {
            towerTexture.loadFromFile("bin/content/textures/MagicTower.png");
            textures["magicTower"] = towerTexture;
            towerSprite.setTexture(textures["magicTower"]);
        }
        float scaleX = (MAP_SIZE / size) / towerTexture.getSize().x;
        float scaleY = (MAP_SIZE / size) / towerTexture.getSize().y;
        towerSprite.setScale(scaleX, scaleY);
        int newX = MAP_OFFSET_X + x *  (MAP_SIZE / size);
        int newY = MAP_OFFSET_Y + y * (MAP_SIZE / size);
        towerSprite.setPosition(newX, newY);
        sprites.push_back(towerSprite);
        std::cout << "TowerTexture\n" << newX << std::endl << newY << "ed\n";
        window->draw(towerSprite);
        return towerSprite;
    }
    sf::Sprite addTrapTexture(int x, int y, int size){
        sf::Sprite trapSprite;
        sf::Texture trapTexture;
        trapTexture.loadFromFile("bin/content/textures/Trap.png");
        textures["trap"] = trapTexture;
        trapSprite.setTexture(textures["trap"]);
        float scaleX = (MAP_SIZE / size) / trapTexture.getSize().x;
        float scaleY = (MAP_SIZE / size) / trapTexture.getSize().y;
        trapSprite.setScale(scaleX, scaleY);
        int newX = MAP_OFFSET_X + x *  (MAP_SIZE / size);
        int newY = MAP_OFFSET_Y + y * (MAP_SIZE / size);
        trapSprite.setPosition(newX, newY);
        sprites.push_back(trapSprite);
//        window.draw(forestSprite);
        return trapSprite;
    }
    void mapTextureInitial(Landscape& landscape){
        sf::Sprite sprite;
        addInterfaceTexture();
//        addTimer();


        for (auto it = landscape.begin(); it != landscape.end(); it++){
            if ((*it).type == forest){
                if ((*it).building){
                    if ((*it).building->getType() == castle_){
                        addCastleTexture(it.getX(), it.getY(), it.getSize());
                        //
                    }
                    else {
                        addLairTexture(it.getX(), it.getY(), it.getSize());

                    }
                }
                else {
                    addForestTexture(it.getX(), it.getY(), it.getSize());
                }
            }
            else if ((*it).type == road){
                addRoadTexture(it.getX(), it.getY(), it.getSize());
            }
            else if ((*it).type == field){
                addFieldTexture(it.getX(), it.getY(), it.getSize());
            }
        }
    }

    void mapTextureDraw() {
        backgroundTextureDraw();
        for (auto sprite = sprites.begin(); sprite != sprites.end(); sprite++){
            window->draw(*sprite);
        }
// Timer

    }

    void infoDraw(int currentTime, int castleGold, int castleHP){
        sf::Font font;
        font.loadFromFile("bin/content/fonts/arialmt.ttf");
        sf::Text timer("Time: " + std::to_string(currentTime), font, 40);
        timer.setFillColor(sf::Color::Black);
        timer.setPosition(TIMER_OFFSET_X, TIMER_OFFSET_Y);
        window->draw(timer);

// CastleGold

        sf::Text castleG("Gold: " + std::to_string(castleGold), font, 40);
        castleG.setFillColor(sf::Color::Black);
        castleG.setPosition(GOLD_OFFSET_X, GOLD_OFFSET_Y);
        window->draw(castleG);
// Castle health

        sf::Text castleHealth("Castle health: " + std::to_string(castleHP), font, 40);
        castleHealth.setFillColor(sf::Color::Black);
        castleHealth.setPosition(HEALTH_OFFSET_X, HEALTH_OFFSET_Y);
        window->draw(castleHealth);

    }

};






#endif //TOWERDEFENCE_TEXTURELOADER_HPP
