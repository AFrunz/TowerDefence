#ifndef TOWERDEFENCE_TOWER_HPP
#define TOWERDEFENCE_TOWER_HPP

#include "Spell.hpp"
#include "Building.hpp"
#include "Enemy.hpp"
//#include "Settings.cpp"

class TowerFeature{
public:
    int damage;
    int radius;
    int price;
};

const int MAX_LVL_OF_BASE_TOWER = 2;
const int MAX_LVL_OF_MAGIC_TOWER = 2;
const TowerFeature BaseTowerLVL[] = {{1, 1, 100}, {1, 2, 200}, {2, 3, 500}};
const TowerFeature MagicTowerLVL[] = {{1, 1, 200}, {2, 1, 400}, {2, 2, 500}};

///Башня
class Tower:public Building{

protected:
    int lvl;
    TowerFeature features;
public:
    Tower();
    int getType() const;
    int getLvl() const;
    int getArea() const;
    virtual void lvlUp() = 0;
    virtual int hit(Enemy* target) = 0;
};


class BaseTower:public Tower{
public:
    BaseTower();
    void lvlUp() override;
    int hit(Enemy* target) override;
};

class MagicTower:public Tower{
private:
    Spell* towerSpell;
public:
    MagicTower();
    void lvlUp() override;
    int hit(Enemy* target) override;
};


#endif //TOWERDEFENCE_TOWER_HPP
