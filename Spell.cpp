#include "headers/Spell.hpp"


Spell::Spell():time(0), power(0) {}

Spell::Spell(int time_, int power_):time(time_), power(power_) {}

int Spell::getType() const {
    return 0;
}

int Spell::getTime() const {
    return time;
}

int Spell::getPower() const {
    return power;
}

//int Spell::addTime(int t) {
//    return 0;
//}
//
//int Spell::addPower(int p) {
//    return 0;
//}

SlowingSpell::SlowingSpell():Spell(){}

SlowingSpell::SlowingSpell(int time, int power) : Spell(time, power) {}

int SlowingSpell::getType() const {
    return 1;
}


PoisoningSpell::PoisoningSpell():Spell() {}

PoisoningSpell::PoisoningSpell(int time, int power) : Spell(time, power) {}

int PoisoningSpell::getType() const {
    return 2;
}

DebilitationSpell::DebilitationSpell():Spell() {}

DebilitationSpell::DebilitationSpell(int time, int power) : Spell(time, power) {}

int DebilitationSpell::getType() const {
    return 3;
}
