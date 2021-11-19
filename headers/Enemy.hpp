#ifndef TOWERDEFENCE_ENEMY_HPP
#define TOWERDEFENCE_ENEMY_HPP

#include "Spell.hpp"
#include "Building.hpp"


///Враг
class Enemy: public Building{

private:
    int x, y;                   /// Координаты
    int direction;
    std::string name;           /// Имя врага
    int maxHp;                  /// Максимальное здоровье
    int currentHp;              /// Текущее здоровье
    int gold;                   /// Количество золота
    int speed;                  /// Скорость передвижения
    std::set<Spell> spellList;  /// Таблица эффектов (мб заменена на multiset)

public:
    // Конструкторы
    Enemy();
    Enemy(std::string name_, int maxHp_, int gold_, int speed_, int x_, int y_);
    // Селекторы
    std::string getName() const;
    int getMaxHp() const;
    int getCurrentHp() const;
    int getGold() const;
    int getSpeed() const;
    void makeMove();            /// Сделать ход
    int reduceHp();            /// Получить урон
    int addSpell();             /// Добавить эффект
    void setDirection(int direction);
    int getDirection();
    int getType();
};






#endif //TOWERDEFENCE_ENEMY_HPP
