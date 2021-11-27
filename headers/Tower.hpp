#ifndef TOWERDEFENCE_TOWER_HPP
#define TOWERDEFENCE_TOWER_HPP

#include "Spell.hpp"
#include "Building.hpp"
#include "Enemy.hpp"
#include "Settings.cpp"

///Башня
class Tower:public Building{

protected:
    int lvl;
    TowerFeature features;
    // таблица характеристик // Отдельный класс??
public:
    Tower();
    int getLvl() const;
    virtual int getArea() const;
    virtual void lvlUp();
    virtual int hit(Enemy* target) = 0;
};

class BaseTower:public Tower{

public:
    BaseTower();
    int hit(Enemy* target);

};

class MagicTower:public Tower{
private:
    Spell* towerSpell;
public:
    MagicTower();
    int hit(Enemy* target) override;
};






#endif //TOWERDEFENCE_TOWER_HPP
