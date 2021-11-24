#ifndef TOWERDEFENCE_LAIR_HPP
#define TOWERDEFENCE_LAIR_HPP


#include "Enemy.hpp"
#include "Building.hpp"
#include <deque>

struct EnemyTime{
    Enemy enemy;
    int time;
};



///Логово
class Lair:public Building{
private:
    std::deque<EnemyTime> timetable;       /// ТАБЛИЦА ОПИСАТЕЛЕЙ ВРАГОВ И ВРЕМЯ ВЫХОДА ИЗ ЛОГОВА
public:
    Lair();
    Enemy* releaseEnemy(int time);             // Возможно добавить ландшафт в список параметров
    bool hasEnemies();
    virtual ~Lair() = default;
};

#endif //TOWERDEFENCE_LAIR_HPP
