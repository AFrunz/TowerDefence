#ifndef TOWERDEFENCE_LANDSCAPE_HPP
#define TOWERDEFENCE_LANDSCAPE_HPP

#include "Building.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include "Trap.hpp"
#include "Castle.hpp"
#include "Lair.hpp"
#include <list>
#include <vector>
#include <ctime>






/// Побочный класс для хранения сведений о позиции врага
//struct UnitPos{
//    double x, y;
//    Enemy* enemy;
//    UnitPos():x(0), y(0), enemy(nullptr){};
//    UnitPos(double x, double y, Enemy* t){
//        this->x = x;
//        this->y = y;
//        enemy = t;
//    }
//};

/// Побочный класс для хранения сведений о клетке поля
struct Field{
    int type;
    Building* building;
    Field():type(0), building(nullptr){};
    Field(int type_, Building* building_):type(type_), building(building_){};
};

/// Типы клеток(убрать)
enum FieldTypes{
    road = 1,
    field = 2,
    forest = 3
};

/// Ландшафт
class Landscape{
private:
    int fieldSize;                                   /// Величина игрового поля
    int xCastle;                                     /// Координаты замка
    int yCastle;
    std::list<Enemy*> enemies;                       /// Позиции врагов
    std::vector<std::vector<Field>> table;           /// Информация об игровом поле

public:
    Landscape();
    Landscape(int n);

    int getFieldSize() const;                       /// Получение размеров поля
    void setFieldSize(int n);                             /// Установка размеров поля
    int getTypeOfField(int x, int y) const;               /// Получение типа клетки
    void setTypeOfField(int x, int y, int type);     /// Установка типа клетки
    int checkCorrect() const;                             /// Проверка правильности карты
    void setBuilding(Building* building, int x, int y);                              /// Установка сооружения
    bool checkWay(int x, int y) const;

    int updateSituation(int time);

    std::vector<Enemy *> findEnemiesInTheArea(int x, int y, int r);
    bool findRoad(int &x, int &y, int &direction) const;
};


#endif //TOWERDEFENCE_LANDSCAPE_HPP
