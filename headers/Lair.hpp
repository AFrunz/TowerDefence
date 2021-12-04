#ifndef TOWERDEFENCE_LAIR_HPP
#define TOWERDEFENCE_LAIR_HPP


#include "Enemy.hpp"
#include "Building.hpp"
#include <list>
//#include "list.hpp"
using std::list;


class Enemy;

/// Элемент таблицы
struct EnemyTime{
    Enemy* enemy;               ///< Указатель на врага
    int time;                   ///< Время выхода
    EnemyTime() = default;
    EnemyTime(std::string name_, int maxHp_, int gold_, int speed_, int time_):time(time_){
        enemy = new Enemy(name_, maxHp_, gold_, speed_);
    }
    ~EnemyTime() = default;
};



///Логово
class Lair:public Building{
private:
    list<EnemyTime> timetable;          ///< Таблица описателей врагов и время выхода из логова
public:
    Lair();
    int getType() const;                ///< Получение типа постройки
    void sort();                        ///< Сортировка по времени выхода
    Enemy* releaseEnemy(int time);      ///< Выпустить врага
    void pushEnemy(EnemyTime ceil);     ///< Поместить врага в таблицу
    bool hasEnemies() const;            ///< Указывает наличие врагов в таблице
    virtual ~Lair();
};

#endif //TOWERDEFENCE_LAIR_HPP
