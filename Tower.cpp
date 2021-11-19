#include "headers/Tower.hpp"


Tower::Tower():lvl(0){}

int Tower::getLvl() const {
    return lvl;
}

int Tower::lvlUp() {
    lvl++;
    //вызов новых характеристик
}

int Tower::hit(Enemy *target) {
    return 0;
}

BaseTower::BaseTower() {

}

int BaseTower::lvlUp() {
    return Tower::lvlUp();
}

int BaseTower::hit(Enemy *target) {
    return Tower::hit(target);
}

MagicTower::MagicTower() {

}

int MagicTower::lvlUp() {
    return Tower::lvlUp();
}

int MagicTower::hit(Enemy *target) {
    return Tower::hit(target);
}
