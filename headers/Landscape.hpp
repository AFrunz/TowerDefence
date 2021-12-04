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





/// Побочный класс для хранения сведений о клетке поля
struct Field{
    int type;                           ///< Тип клетки
    Building* building;                 ///< Строение, стоящее на этой клетке
    Field():type(0), building(nullptr){};
    Field(int type_, Building* building_):type(type_), building(building_){};
    ~Field(){
        delete building;
    }
};

/// Типы клеток
enum FieldTypes{
    road = 1,
    field = 2,
    forest = 3
};

/// Ландшафт
class Landscape{
private:
    int fieldSize;                                   ///< Величина игрового поля
    int xCastle;                                     ///< X координата замка
    int yCastle;                                     ///< Y координата замка
    std::list<Enemy*> enemies;                       ///< Позиции врагов
    std::vector<std::vector<Field>> table;           ///< Информация об игровом поле

public:
    Landscape();
    Landscape(int n);

    int getFieldSize() const;                                               ///< Получение размеров поля
    void setFieldSize(int n);                                               ///< Установка размеров поля
    int getTypeOfField(int x, int y) const;                                 ///< Получение типа клетки
    void setTypeOfField(int x, int y, int type);                            ///< Установка типа клетки
    int checkCorrect() const;                                               ///< Проверка правильности карты
    void setBuilding(Building* building, int x, int y);                     ///< Установка сооружения
    bool checkWay(int x, int y) const;                                      ///< Проверка наличия пути от логова до замка

    int updateSituation(int time);                                          ///< Обновление ситуации
    int updateEnemiesPosition();
    std::vector<Enemy *> findEnemiesInTheArea(int x, int y, int r);         ///< Поиск врагов в зоне
    bool findRoad(int &x, int &y, int &direction) const;                    ///< Поиск клетки для хода врага
    int getTypeOfBuilding(int x, int y) const;
    int getCastleGold() const;
    int towerUp(int x, int y);
    int getCastleHealth() const;
    void decreaseCastleGold(int gold);
    ~Landscape();
};


#endif //TOWERDEFENCE_LANDSCAPE_HPP
