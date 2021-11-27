#include "headers/Tower.hpp"


Tower::Tower():lvl(0){
    features = TowerLVL[lvl];
}

int Tower::getLvl() const {
    return lvl;
}

void Tower::lvlUp() {
    lvl++;
    features = TowerLVL[lvl];
}

//int Tower::hit(Enemy *target) {
//    if (!target) return -1;
//    target->reduceHp(features.damage);
//    return 0;
//}

int Tower::getArea() const {
    return features.radius;
}

BaseTower::BaseTower():Tower(){}


int BaseTower::hit(Enemy *target) {
    if (!target) return -1;
    target->reduceHp(features.damage);
    return 0;
}

MagicTower::MagicTower():Tower(){}

int MagicTower::hit(Enemy *target) {
    if (!target) return -1;
    target->reduceHp(features.damage);
    target->addSpell(towerSpell);
    return 0;
}
