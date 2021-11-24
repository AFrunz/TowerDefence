#include "headers/Lair.hpp"


//struct EnemyTime{
//    Enemy enemy;
//    int time;
//};
/////Логово
//class Lair:public Building{
//private:
//    std::deque<EnemyTime> timetable;       /// ТАБЛИЦА ОПИСАТЕЛЕЙ ВРАГОВ И ВРЕМЯ ВЫХОДА ИЗ ЛОГОВА
//public:
//    Lair();
//    int releaseEnemy(int time);             // Возможно добавить ландшафт в список параметров
//};

Lair::Lair():timetable() {}

Enemy* Lair::releaseEnemy(int time) {
    if (timetable.empty()) return nullptr;
    if (timetable.front().time == time){
        Enemy &buf = timetable.front().enemy;
        timetable.pop_front();
        return &buf;
    }
    return nullptr;
}

bool Lair::hasEnemies() {
    return !timetable.empty();
}

