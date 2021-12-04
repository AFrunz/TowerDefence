#include "headers/Tower.hpp"


Tower::Tower():lvl(0){}

int Tower::getLvl() const {
    return lvl;
}

int Tower::getType() const {
    return 2;
}


//int Tower::hit(Enemy *target) {
//    if (!target) return -1;
//    target->reduceHp(features.damage);
//    return 0;
//}

int Tower::getArea() const {
    return features.radius;
}


BaseTower::BaseTower():Tower(){
    features = BaseTowerLVL[lvl];
}

int BaseTower::lvlUp() {
    if (lvl == MAX_LVL_OF_BASE_TOWER) return -1;
    lvl++;
    features = BaseTowerLVL[lvl];
    return 0;
}

int BaseTower::hit(Enemy *target) {
    if (!target) return -1;
    target->reduceHp(features.damage);
    return 0;
}

int BaseTower::getPrice(int lvl) {
    if (lvl <= MAX_LVL_OF_BASE_TOWER){
        return BaseTowerLVL[lvl].price;
    }
    return 0;
}

int BaseTower::getTowerType() const {
    return basic_;
}

MagicTower::MagicTower():Tower(){
    features = MagicTowerLVL[lvl];
}

int MagicTower::lvlUp() {
    if (lvl == MAX_LVL_OF_MAGIC_TOWER) return -1;
    lvl++;
    features = MagicTowerLVL[lvl];
    return 0;
}


int MagicTower::hit(Enemy *target) {
    if (!target) return -1;
    target->reduceHp(features.damage);
    target->addSpell(towerSpell);
    return 0;
}

MagicTower::MagicTower(int type):Tower() {
    features = MagicTowerLVL[lvl];
    if (type == poisoning_){
        towerSpell = new PoisoningSpell(POISONING_SPELL_TIME, POISONING_SPELL_POWER);
    }
    else if (type == slowing_){
        towerSpell = new SlowingSpell(SLOWING_SPELL_TIME, SLOWING_SPELL_POWER);
    }
    else if (type == debilitation_){
        towerSpell = new DebilitationSpell(DEBILITATION_SPELL_TIME, DEBILITATION_SPELL_POWER);
    }
}

int MagicTower::getPrice(int lvl) {
    if (lvl <= MAX_LVL_OF_MAGIC_TOWER){
        return MagicTowerLVL[lvl].price;
    }
    return 0;
}

int MagicTower::getTowerType() const {
    return magic_;
}

MagicTower::~MagicTower() {
    delete towerSpell;
}

