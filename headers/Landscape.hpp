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
//#include "TextureLoader.hpp"






/// Побочный класс для хранения сведений о клетке поля
struct Field{
    int type;                           ///< Тип клетки
    Building* building;                 ///< Строение, стоящее на этой клетке
    Field():type(0), building(nullptr){};
    Field(int type_, Building* building_):type(type_), building(building_){};
    ~Field() = default;
};

/// Типы клеток
enum FieldTypes{
    road = 1,
    field = 2,
    forest = 3
};


class TextureLoader;

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
    class iterator{
    private:
        int x, y, size;
        std::vector<std::vector<Field>> *table;
    public:
        iterator() = default;
        friend class Landscape;
        int getX() const{
            return y;
        }
        int getY() const{
            return x;
        }
        int getSize() const{
            return size;
        }
        const Field& operator* (){
            if (x < size){
                return (*table)[x][y];
            }
            else {
                x = 0;
                y++;
                return (*table)[x][y];
            }
        }
        iterator& operator++ (){
            x++;
            if (x == size){
                x = 0;
                y++;
            }
            return *this;
        }

        iterator& operator++ (int){
            x++;
            if (x == size){
                x = 0;
                y++;
            }
            return *this;
        }

        friend bool operator== (const iterator& a, const iterator& b){
            return (a.x == b.x) && (a.y == b.y) && (a.size == b.size) && (a.table == b.table);
        }

        friend bool operator!= (const iterator& a, const iterator& b){
            return (a.x != b.x) || (a.y != b.y) || (a.size != b.size) || (a.table != b.table);
        }

        ~iterator() = default;
    };
    int getFieldSize() const;                                               ///< Получение размеров поля
    void setFieldSize(int n);                                               ///< Установка размеров поля
    int getTypeOfField(int x, int y) const;                                 ///< Получение типа клетки
    void setTypeOfField(int x, int y, int type);                            ///< Установка типа клетки
    int checkCorrect() const;                                               ///< Проверка правильности карты
    void setBuilding(Building* building, int x, int y);                     ///< Установка сооружения
    bool checkWay(int x, int y) const;                                      ///< Проверка наличия пути от логова до замка

    int updateSituation(int time, std::vector<int>& c);                                          ///< Обновление ситуации
    int updateEnemiesPosition(std::vector<int>& c);
    std::vector<Enemy *> findEnemiesInTheArea(int x, int y, int r);         ///< Поиск врагов в зоне
    bool findRoad(int &x, int &y, int &direction) const;                    ///< Поиск клетки для хода врага
    int getTypeOfBuilding(int x, int y) const;
    int getCastleGold() const;
    int towerUp(int x, int y);
    int getCastleHealth() const;
    void decreaseCastleGold(int gold);
    iterator begin(){
        iterator it;
        it.x = 0;
        it.y = 0;
        it.table = &table;
        it.size = fieldSize;
        return it;
    }
    iterator end(){
        iterator it;
        it.x = 0;
        it.y = fieldSize;
        it.table = &table;
        it.size = fieldSize;
        return it;
    }

    ~Landscape();
};




#endif //TOWERDEFENCE_LANDSCAPE_HPP
