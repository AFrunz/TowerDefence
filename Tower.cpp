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

void BaseTower::lvlUp() {
    if (lvl == MAX_LVL_OF_BASE_TOWER) return;
    lvl++;
    features = BaseTowerLVL[lvl];
}

int BaseTower::hit(Enemy *target) {
    if (!target) return -1;
    target->reduceHp(features.damage);
    return 0;
}

MagicTower::MagicTower():Tower(){
    features = MagicTowerLVL[lvl];
}

void MagicTower::lvlUp() {
    if (lvl == MAX_LVL_OF_MAGIC_TOWER) return;
    lvl++;
    features = MagicTowerLVL[lvl];
}


int MagicTower::hit(Enemy *target) {
    if (!target) return -1;
    target->reduceHp(features.damage);
    target->addSpell(towerSpell);
    return 0;
}

MagicTower::MagicTower(int type):Tower() {
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
