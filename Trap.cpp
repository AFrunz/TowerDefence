#include "headers/Trap.hpp"




Trap::Trap():spell(nullptr), radius(0){}

Trap::Trap(int type, int radius_):radius(radius_){
    if (type == poisoning_){
        spell = new PoisoningSpell(POISONING_SPELL_TIME, POISONING_SPELL_POWER);
    }
    else if (type == slowing_){
        spell = new SlowingSpell(SLOWING_SPELL_TIME, SLOWING_SPELL_POWER);
    }
    else if (type == debilitation_){
        spell = new DebilitationSpell(DEBILITATION_SPELL_TIME, DEBILITATION_SPELL_POWER);
    }
}

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

Trap::~Trap() {
    delete spell;
}



