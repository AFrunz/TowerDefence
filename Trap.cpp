#include "headers/Trap.hpp"




Trap::Trap():spell(nullptr), radius(0){}

Trap::Trap(Spell *spell_, int radius_):spell(spell_), radius(radius_){}

int Trap::getArea() const{
    return radius;
}

int Trap::hit(Enemy *target) {
    if (!target) return -1;
    target->addSpell(spell);
    return 0;
}

int Trap::getType() const{
    return 4;
}



