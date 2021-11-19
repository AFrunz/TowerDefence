#include "headers/Enemy.hpp"


//int x, y;                   /// Координаты
//int direction;
//std::string name;           /// Имя врага
//int maxHp;                  /// Максимальное здоровье
//int currentHp;              /// Текущее здоровье
//int gold;                   /// Количество золота
//int speed;                  /// Скорость передвижения
//std::set<Spell> spellList;  /// Таблица эффектов (мб заменена на multiset)

Enemy::Enemy():x(-1), y(-1), direction(0), name(), maxHp(0), currentHp(0), gold(0), speed(0), spellList(){}

Enemy::Enemy(std::string name_, int maxHp_, int gold_, int speed_, int x_, int y_):name(name_), maxHp(maxHp_),
gold(gold_), speed(speed_), x(x_), y(y_), spellList(){}

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

void Enemy::makeMove() {

}

int Enemy::reduceHp() {
    return 0;
}



