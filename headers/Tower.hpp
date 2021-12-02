#ifndef TOWERDEFENCE_TOWER_HPP
#define TOWERDEFENCE_TOWER_HPP

#include "Spell.hpp"
#include "Building.hpp"
#include "Enemy.hpp"

/// Характеристики башни
class TowerFeature{
public:
    int damage;         ///< Урон
    int radius;         ///< Радиус обстрела
    int price;          ///< Цена
};

const int MAX_LVL_OF_BASE_TOWER = 2;
const int MAX_LVL_OF_MAGIC_TOWER = 2;
const TowerFeature BaseTowerLVL[] = {{5, 1, 100}, {10, 2, 200}, {10, 3, 500}};
const TowerFeature MagicTowerLVL[] = {{5, 1, 200}, {8, 1, 400}, {10, 2, 500}};

///Башня
class Tower:public Building{

protected:
    int lvl;                    ///< Уровень башни
    TowerFeature features;      ///< Характеристики башни
public:
    Tower();
    int getType() const;                    ///< Получение типа постройки
    int getLvl() const;                     ///< Получение уровня башни
    int getArea() const;                    ///< Получение радиуса обстрела
    virtual void lvlUp() = 0;               ///< Повышение уровня
    virtual int hit(Enemy* target) = 0;     ///< Нанесение урона врагу
};

/// Обычная башня
class BaseTower:public Tower{
public:
    BaseTower();
    void lvlUp() override;                  ///< Повышение уровня
    int hit(Enemy* target) override;        ///< Нанесение урона врагу
};


/// Магическая башня
class MagicTower:public Tower{
private:
    Spell* towerSpell;                      ///< Эффекты, накладываемые башней
public:
    MagicTower();
    void lvlUp() override;                  ///< Повышение уровня
    int hit(Enemy* target) override;        ///< Нанесение урона врагу
};


#endif //TOWERDEFENCE_TOWER_HPP
