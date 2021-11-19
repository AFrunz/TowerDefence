#ifndef TOWERDEFENCE_TOWER_HPP
#define TOWERDEFENCE_TOWER_HPP

#include "Spell.hpp"
#include "Building.hpp"
#include "Enemy.hpp"


///Башня
class Tower:public Building{

protected:
    int lvl;
    // таблица характеристик // Отдельный класс??
public:
    Tower();
    int getLvl() const;
    virtual int getArea() const;
    virtual int lvlUp();
    virtual int hit(Enemy* target);
};

class BaseTower:public Tower{

public:
    BaseTower();
    int lvlUp() override;
    int hit(Enemy* target);

};

class MagicTower:public Tower{
private:
    Spell towerSpell;
public:
    MagicTower();
    int lvlUp() override;
    int hit(Enemy* target);
};






#endif //TOWERDEFENCE_TOWER_HPP
