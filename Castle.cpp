#include "headers/Castle.hpp"

//private:
//std::string name;           /// Имя замка
//int maxHp;                  /// Максимальное здоровье
//int currentHp;              /// Текущее здоровье
//int gold;                   /// Золото


Castle::Castle():name(), maxHp(0), currentHp(0), gold(0){}


Castle::Castle(std::string name_, int maxHealthPoint, int startGold = 100):name(name_), maxHp(maxHealthPoint),
currentHp(maxHealthPoint), gold(startGold){}


int Castle::getGold() const {
    return gold;
}

int Castle::getMaxHp() const {
    return maxHp;
}

int Castle::getCurrentHp() const {
    return currentHp;
}

std::string Castle::getName() const {
    return name;
}

void Castle::damage(const Enemy& enemy) {
    int dam = enemy.getCurrentHp();
    currentHp -= dam;
}

void Castle::increaseGold(const Enemy &enemy) {
    int enemyGold = enemy.getGold();
    gold += enemyGold;
}
