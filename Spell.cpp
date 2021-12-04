#include "headers/Spell.hpp"

// Global spell

Spell::Spell():time(0), power(0) {}

Spell::Spell(int time_, int power_):time(time_), power(power_) {}

int Spell::getTime() const {
    return time;
}

int Spell::getPower() const {
    return power;
}


int Spell::setTime(int t) {
    if (t < 0) return -1;
    time = t;
    return 0;
}

int Spell::setPower(int p) {
    if (p < 0) return -1;
    power = p;
    return 0;
}

void Spell::decreaseTime(int t) {
    time -= t;
    if (time < 0) time = 0;
}


// Slowing Spell

SlowingSpell::SlowingSpell():Spell(){}

SlowingSpell::SlowingSpell(int time, int power) : Spell(time, power) {}

int SlowingSpell::getType() const {
    return slowing_;
}

//Poisoning spell

PoisoningSpell::PoisoningSpell():Spell() {}

PoisoningSpell::PoisoningSpell(int time, int power) : Spell(time, power) {}

int PoisoningSpell::getType() const {
    return poisoning_;
}

// Debilitation spell


DebilitationSpell::DebilitationSpell():Spell() {}

DebilitationSpell::DebilitationSpell(int time, int power) : Spell(time, power) {}

int DebilitationSpell::getType() const {
    return debilitation_;
}
