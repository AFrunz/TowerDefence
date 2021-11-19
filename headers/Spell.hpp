#ifndef TOWERDEFENCE_SPELL_HPP
#define TOWERDEFENCE_SPELL_HPP
#include <iostream>
#include <map>
#include <set>

///Эффект
class Spell{
protected:
    int time;                   /// Время действия эффекта
    int power;                  /// Мощность эффекта

public:
    Spell();
    Spell(int time, int power);

    virtual int getType() const;
    int getTime() const;
    int getPower() const;
    int addTime(int t);         /// Добавление времени
    int addPower(int p);        /// Добавление мощности ( в зависимости от условия)
};


/// Замедляющий эффект
class SlowingSpell:public Spell{

public:
    SlowingSpell();
    SlowingSpell(int time, int power);
    int getType() const;
};

///Отравляющий эффект
class PoisoningSpell:public Spell{

public:
    PoisoningSpell();
    PoisoningSpell(int time, int power);
    int getType() const;
};

///Ослабляющий эффект
class DebilitationSpell:public Spell{

public:
    DebilitationSpell();
    DebilitationSpell(int time, int power);
    int getType() const;
};









#endif //TOWERDEFENCE_SPELL_HPP
