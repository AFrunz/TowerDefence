#ifndef TOWERDEFENCE_LAIR_HPP
#define TOWERDEFENCE_LAIR_HPP


#include "Enemy.hpp"
#include "Building.hpp"
#include <list>
//#include "list.hpp"
//using std::list;
//using std::list;


class Enemy;

struct EnemyTime{
    Enemy* enemy;
    int time;
    EnemyTime() = default;
    EnemyTime(std::string name_, int maxHp_, int gold_, int speed_, int time_):time(time_){
        enemy = new Enemy(name_, maxHp_, gold_, speed_);
    }


};



///Логово
class Lair:public Building{
private:
    list<EnemyTime> timetable;       /// ТАБЛИЦА ОПИСАТЕЛЕЙ ВРАГОВ И ВРЕМЯ ВЫХОДА ИЗ ЛОГОВА
public:
    Lair();
    int getType() const;
    void sort();
    Enemy* releaseEnemy(int time);
    void pushEnemy(EnemyTime ceil);
    bool hasEnemies() const;
    virtual ~Lair() = default;
};

#endif //TOWERDEFENCE_LAIR_HPP
