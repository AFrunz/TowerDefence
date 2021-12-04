#ifndef TOWERDEFENCE_TRAP_HPP
#define TOWERDEFENCE_TRAP_HPP

#include "Building.hpp"
#include "Spell.hpp"
#include "Enemy.hpp"
#include "settings.h"



/// Ловушка
class Trap:public Building{
    Spell* spell;                               ///< Эффект
    int radius;                                 ///< Радиус поражения
public:
    Trap();
    Trap(int type, int radius_ = TRAP_RADIUS);
    int getType() const;                        ///< Получение типа здания
    int getArea() const;                        ///< Получение радиуса поражения
    int hit(Enemy* target);                     ///< Наложить эффект на врага
    virtual ~Trap();
};




#endif //TOWERDEFENCE_TRAP_HPP
