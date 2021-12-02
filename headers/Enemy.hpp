#ifndef TOWERDEFENCE_ENEMY_HPP
#define TOWERDEFENCE_ENEMY_HPP

#include "Spell.hpp"
#include "Building.hpp"
#include <list>

///Враг
class Enemy{

private:
    int x, y;                    ///< Координаты
    int direction;               ///< Направление движения
    std::string name;            ///< Имя врага
    int maxHp;                   ///< Максимальное здоровье
    int currentHp;               ///< Текущее здоровье
    int gold;                    ///< Количество золота
    int speed;                   ///< Скорость передвижения
    std::list<Spell*> spellList;  ///< Таблица эффектов

public:
    // Конструкторы
    Enemy();
    Enemy(std::string name_, int maxHp_, int gold_, int speed_);
    // Селекторы
    int getX() const{return x;};                                    ///< Получение x координаты
    int getY() const{return y;};                                    ///< Получение y координаты
    std::string getName() const;                                    ///< Получение имени
    int getMaxHp() const;                                           ///< Получение максимального здоровья
    int getCurrentHp() const;                                       ///< Получение текущего здоровья
    int getGold() const;                                            ///< Получение количества золота
    int getSpeed() const;                                           ///< Получение скорости врага
    int getDirection() const;                                       ///< Получение направления движения
    void move(int x_, int y_, int direction);                       ///< Перемещение на координаты (x,y)
    void reduceHp(int damage);                                      ///< Получить урон
    void addSpell(const Spell* spell);                                    ///< Добавить эффект
    void takeDamageFromPoison();
    virtual ~Enemy() = default;
};






#endif //TOWERDEFENCE_ENEMY_HPP
