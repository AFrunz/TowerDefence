#include "headers/Enemy.hpp"


Enemy::Enemy():x(-1), y(-1), direction(0), name(), maxHp(0), currentHp(0), gold(0), speed(0), spellList(){}

Enemy::Enemy(std::string name_, int maxHp_, int gold_, int speed_):name(name_), maxHp(maxHp_),
gold(gold_), speed(speed_), x(-1), y(-1), spellList(), direction(0), currentHp(maxHp_){
}

Enemy::Enemy(std::string name_, int maxHp_, int gold_, int speed_, sf::RenderWindow* window_):name(name_), maxHp(maxHp_),
                                                                   gold(gold_), speed(speed_), x(-1), y(-1), spellList(),
                                                                   direction(0), currentHp(maxHp_), enemyTexture(),
                                                                   enemySprite(){
    window = window_;
    enemyTexture.loadFromFile(ENEMY_TEXTURE_PATH);
    enemySprite.setTexture(enemyTexture);
}

std::string Enemy::getName() const {
    return name;
}

int Enemy::getMaxHp() const {
    return maxHp;
}

int Enemy::getCurrentHp() const {
    return currentHp;
}

int Enemy::getGold() const {
    return gold;
}

int Enemy::getSpeed() const {
    return speed;
}

void Enemy::reduceHp(int damage) {
    int power = getIncreasedDamageInPercents();
    currentHp -= static_cast<int>(damage * power / 100);
    if (currentHp < 0) currentHp = 0;
}

void Enemy::move(int x_, int y_, int direction_, int size) {
    if (x_ < 0 || y_ < 0) throw std::runtime_error("Wrong cords\n");
    x = x_;
    y = y_;
    direction = direction_;

    float scaleX = (MAP_SIZE / size) / enemyTexture.getSize().x;
    float scaleY = (MAP_SIZE / size) / enemyTexture.getSize().y;
    enemySprite.setScale(scaleX, scaleY);
    int newX = MAP_OFFSET_X + y *  (MAP_SIZE / size);
    int newY = MAP_OFFSET_Y + x * (MAP_SIZE / size);
    enemySprite.setPosition(newX, newY);
    window->draw(enemySprite);
}


int Enemy::getDirection() const{
    return direction;
}


void Enemy::addSpell(const Spell* spell) {
    if (spell) {
        Spell *spell_ = nullptr;
        if (spell->getType() == slowing_) {
            spell_ = new SlowingSpell;
        }
        else if (spell->getType() == debilitation_){
            spell_ = new DebilitationSpell;
        }
        else if (spell->getType() == poisoning_){
            spell_ = new PoisoningSpell;
        }
        if (spell_) {
            spell_->setPower(spell->getPower());
            spell_->setTime(spell->getTime());
            spellList.push_back(spell_);
        }
    }
}

void Enemy::takeDamageFromPoison() {
    auto it = spellList.begin();
    while (it != spellList.end()){
        if ((*it)->getType() == poisoning_){
            currentHp -= (*it)->getPower();
            if (currentHp < 0) currentHp = 0;
        }
        it++;
    }
}

void Enemy::decreaseSpellTime() {
    auto it = spellList.begin();
    while (it != spellList.end()){
        (*it)->decreaseTime();
        if ((*it)->getTime() <= 0){
            delete (*it);
            it = spellList.erase(it);
            continue;
        }
        it++;
    }
}

int Enemy::getIncreasedDamageInPercents() const{
    auto it = spellList.begin();
    int percents = 100;
    while (it != spellList.end()){
        if ((*it)->getType() == debilitation_){
            percents += (*it)->getPower();
        }
        it++;
    }
    return percents;
}

Enemy::~Enemy() {
    auto it = spellList.begin();
    while (it != spellList.end()){
        delete (*it);
        it++;
    }
}
