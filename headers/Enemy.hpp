#ifndef TOWERDEFENCE_ENEMY_HPP
#define TOWERDEFENCE_ENEMY_HPP

#include "Spell.hpp"
#include "Building.hpp"


///Враг
class Enemy{

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
    int getX() const{return x;};
    int getY() const{return y;};
    void move(int x_, int y_);
    std::string getName() const;
    int getMaxHp() const;
    int getCurrentHp() const;
    int getGold() const;
    int getSpeed() const;
    void reduceHp(int damage);            /// Получить урон
    void addSpell(Spell* spell);             /// Добавить эффект
    void setDirection(int direction);
    int getDirection() const;
    virtual ~Enemy() = default;
};






#endif //TOWERDEFENCE_ENEMY_HPP
