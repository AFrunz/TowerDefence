#ifndef TOWERDEFENCE_SPELL_HPP
#define TOWERDEFENCE_SPELL_HPP
#include <iostream>
#include "settings.h"

enum spellTypes{
    slowing_ = 1,
    poisoning_ = 2,
    debilitation_ = 3
};



///Эффект
class Spell{
protected:
    int time;                   ///< Время действия эффекта
    int power;                  ///< Мощность эффекта

public:
    Spell();
    Spell(int time, int power);
    Spell(const Spell& sp);

    virtual int getType() const = 0;        ///< Получение типа постройки
    int getTime() const;                    ///< Получение времени действия
    int getPower() const;                   ///< Получение мощности
    int setTime(int t);                     ///< Добавление времени
    int setPower(int p);                    ///< Добавление мощности ( в зависимости от условия)
    void decreaseTime(int t = 1);
    virtual ~Spell() = default;
};


/// Замедляющий эффект
class SlowingSpell:public Spell{

public:
    SlowingSpell();
    SlowingSpell(int time, int power);
    virtual int getType() const;            ///< Получение типа постройки
    virtual ~SlowingSpell() = default;
};

///Отравляющий эффект
class PoisoningSpell:public Spell{

public:
    PoisoningSpell();
    PoisoningSpell(int time, int power);
    int getType() const;                    ///< Получение типа постройки
    virtual ~PoisoningSpell() = default;
};

///Ослабляющий эффект
class DebilitationSpell:public Spell{

public:
    DebilitationSpell();
    DebilitationSpell(int time, int power);
    int getType() const;                    ///< Получение типа постройки
    virtual ~DebilitationSpell() = default;
};









#endif //TOWERDEFENCE_SPELL_HPP
