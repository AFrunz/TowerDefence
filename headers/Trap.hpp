#ifndef TOWERDEFENCE_TRAP_HPP
#define TOWERDEFENCE_TRAP_HPP

#include "Building.hpp"
#include "Spell.hpp"
#include "Enemy.hpp"

/// Ловушка (мб можно будет обойтись классом эффект)
class Trap:public Building{
    Spell* spell;
    int radius;
public:
    Trap();
    Trap(Spell* spell_, int radius_);
    int getType() const;
    int getArea() const;
    int hit(Enemy* target);
    virtual ~Trap() = default;
};




#endif //TOWERDEFENCE_TRAP_HPP
