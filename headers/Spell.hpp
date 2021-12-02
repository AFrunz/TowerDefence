#ifndef TOWERDEFENCE_SPELL_HPP
#define TOWERDEFENCE_SPELL_HPP
#include <iostream>

///Эффект
class Spell{
protected:
    int time;                   ///< Время действия эффекта
    int power;                  ///< Мощность эффекта

public:
    Spell();
    Spell(int time, int power);

    virtual int getType() const = 0;        ///< Получение типа постройки
    int getTime() const;                    ///< Получение времени действия
    int getPower() const;                   ///< Получение мощности
    int addTime(int t);                     ///< Добавление времени
    int addPower(int p);                    ///< Добавление мощности ( в зависимости от условия)
};


/// Замедляющий эффект
class SlowingSpell:public Spell{

public:
    SlowingSpell();
    SlowingSpell(int time, int power);
    virtual int getType() const;            ///< Получение типа постройки
};

///Отравляющий эффект
class PoisoningSpell:public Spell{

public:
    PoisoningSpell();
    PoisoningSpell(int time, int power);
    int getType() const;                    ///< Получение типа постройки
};

///Ослабляющий эффект
class DebilitationSpell:public Spell{

public:
    DebilitationSpell();
    DebilitationSpell(int time, int power);
    int getType() const;                    ///< Получение типа постройки
};









#endif //TOWERDEFENCE_SPELL_HPP
