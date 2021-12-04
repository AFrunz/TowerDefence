#include "headers/Lair.hpp"


//struct EnemyTime{
//    Enemy enemy;
//    int time;
//};
//Логово
//class Lair:public Building{
//private:
//    std::list<EnemyTime> timetable;       /// ТАБЛИЦА ОПИСАТЕЛЕЙ ВРАГОВ И ВРЕМЯ ВЫХОДА ИЗ ЛОГОВА
//public:
//    Lair();
//    int releaseEnemy(int time);             // Возможно добавить ландшафт в список параметров
//};

Lair::Lair():timetable() {}

Enemy* Lair::releaseEnemy(int time) {
    if (timetable.empty()) return nullptr;
    if (timetable.front().time == time){
        Enemy* buf = timetable.front().enemy;
        timetable.pop_front();
        return buf;
    }
    return nullptr;
}

bool Lair::hasEnemies() const{
    return !timetable.empty();
}

int Lair::getType() const {
    return 1;
}

void Lair::sort() {
    auto itSt = timetable.begin();
    auto itEn = timetable.end();
//    std::sort(itSt, itEn, [](EnemyTime& a, EnemyTime& b){
//        return a.time < b.time;
//    });
    timetable.sort([](EnemyTime& a, EnemyTime& b){
        return a.time < b.time;
    });
}

void Lair::pushEnemy(EnemyTime ceil) {
    timetable.push_back(ceil);
    sort();
}

Lair::~Lair() {
    for (auto enemy : timetable){
        delete enemy.enemy;
    }
}

