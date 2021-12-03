#include "headers/Enemy.hpp"


Enemy::Enemy():x(-1), y(-1), direction(0), name(), maxHp(0), currentHp(0), gold(0), speed(0), spellList(){}

Enemy::Enemy(std::string name_, int maxHp_, int gold_, int speed_):name(name_), maxHp(maxHp_),
gold(gold_), speed(speed_), x(-1), y(-1), spellList(), direction(0), currentHp(maxHp_){}

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
    currentHp -= damage;
    if (currentHp < 0) currentHp = 0;
}

void Enemy::move(int x_, int y_, int direction_) {
    if (x_ < 0 || y_ < 0) throw std::runtime_error("Wrong cords\n");
    x = x_;
    y = y_;
    direction = direction_;
}


int Enemy::getDirection() const{
    return direction;
}
/*/////////////////////////////////////////////*/
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
        if ((*it)->getTime() <= 0){
            it = spellList.erase(it);
            continue;
        }
        if ((*it)->getType() == 2){
            currentHp -= (*it)->getPower();
            if (currentHp < 0) currentHp = 0;
        }
        it++;
    }
}
