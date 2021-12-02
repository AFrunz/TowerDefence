#ifndef TOWERDEFENCE_TOWERDEFENCE_H
#define TOWERDEFENCE_TOWERDEFENCE_H
#include "Landscape.hpp"
#include <map>
#include <fstream>

/// Счетчик времени
class Timer{
private:
    double timeStart;                   /// Начало отсчета
    double currentTime;                 /// Текущее время
    double speed;                       /// Скорость течения времени
    int units;                          /// Время в условных единицах
public:
    Timer();
    int getTimeInUnits();               /// Получение времени в условных единицах
    void setTimeout(double t);          /// Установка задержки
    void setSpeed(double speed_ = 1);   /// Установка скорости течения времени
};

// Побочный класс для хранения сведений о клетке поля
//struct Field{
//    int type;
//    Building* building;
//    Field():type(0), building(nullptr){};
//    Field(int type_, Building* building_):type(type_), building(building_){};
//};
//
// Типы клеток(убрать)
//enum FieldTypes{
//    road = 1,
//    field = 2,
//    forest = 3
//};
//L - layer
//        F - forest
//        R - road
//        C - castle
//        I - field
// map:
// 2FFFF

// Castle:
// name\n
// maxHp
// gold

// Lair
// count
// name
// maxhp
// gold
// speed
// time

const std::string logFileName = "/mnt/c/Users/frunz/Desktop/c_or_c++/TowerDefenceV2/settingFiles/log.txt";

/// Общий класс-интерфейс
class TowerDefence {
private:
    Landscape landscape;                        /// Ландшафт
    Timer timer;                                /// Счетчик времени
public:
    TowerDefence():landscape(), timer(){};

    Landscape getLandscapeCopy(){return landscape;};    /// Получение копии ландшафта(для тестов)

    int getTime(){
        return timer.getTimeInUnits();
    }

/// Загрузка замка из потока
    Castle* loadCastle(std::istream &CastleInput){
        std::string name;
        CastleInput >> name;
        if (!CastleInput.good()) throw std::runtime_error("Bad castle file\n");
        int maxHp;
        int gold = -1;
        CastleInput >> maxHp;
        if (!CastleInput.good()) throw std::runtime_error("Bad castle file\n");
        CastleInput >> gold;
        if (CastleInput.bad() || CastleInput.fail()) throw std::runtime_error("Bad castle file\n");
        Castle* castle = new Castle(name, maxHp, gold);
        return castle;
    }

/// Загрузка логова из потока
    Lair* loadLair(std::istream &LairInput){
        int num;                // Количество врагов в логове
        LairInput >> num;
        Lair* lair = new Lair;
        if (!LairInput.good() || LairInput.eof()) throw std::runtime_error("Bad lair file\n");
        for (int i = 0; i < num; i++){
            std::string name;
            int maxHp;
            int gold;
            double speed;
            int time;
            LairInput >> name;
            LairInput >> maxHp;
            LairInput >> gold;
            LairInput >> speed;
            if (!LairInput.good() || LairInput.eof()) throw std::runtime_error("Bad lair file\n");
            LairInput >> time;
            if (!LairInput.good()) throw std::runtime_error("Bad lair file\n");
            EnemyTime ceil(name, maxHp, gold, speed, time);
            lair->pushEnemy(ceil);
        }
        return lair;
    }

/// Загрузка карты из потока
    void loadMap(std::istream &MapInput, std::istream &CastleInput, std::istream &LairInput){
        int num;
        MapInput >> num;
        if (MapInput.eof() || !MapInput.good()) throw std::runtime_error("Bad map file\n");
        char check;
        landscape = Landscape(num);
        for (int i = 0; i < num; i++){
            for (int j = 0; j < num; j++){
                MapInput >> check;
                if (MapInput.eof() || !MapInput.good()) throw std::runtime_error("Bad map file\n");
                if (check == 'F'){
                    landscape.setTypeOfField(i, j, forest);
                }
                else if (check == 'R'){
                    landscape.setTypeOfField(i, j, road);
                }
                else if (check == 'I'){
                    landscape.setTypeOfField(i, j, field);
                }
                else if (check == 'C'){
                    Castle* castle = loadCastle(CastleInput);
                    landscape.setTypeOfField(i, j, forest);
                    landscape.setBuilding(castle, i, j);
                }
                else if (check == 'L'){
                    Lair* lair = loadLair(LairInput);
                    landscape.setTypeOfField(i, j, forest);
                    landscape.setBuilding(lair, i, j);
                }
            }
        }
        landscape.checkCorrect();
    }

/// Создание лога
    void createLog(){
        std::fstream logFile(logFileName);
        logFile << timer.getTimeInUnits() << std::endl;
    }

/// Начало игры
/// Доработать setTimeout
    int startGame(){
        int status = 1;
        while (status != 0){
            status = landscape.updateSituation(timer.getTimeInUnits());
            landscape.updateEnemiesPosition();
            timer.setTimeout(1);
        }
        return status;
    }

    int oneIter(){
        int status = landscape.updateSituation(timer.getTimeInUnits());
        landscape.updateEnemiesPosition();
        timer.setTimeout(1);
        return status;
    }

    void addTower(int x, int y){
        Tower* tower = new BaseTower;
        landscape.setBuilding(tower, y, x);
    }

    void towerUp(int x, int y){
        landscape.towerUp(y, x);
    }

    void print(){
        std::cout << "Time: " << timer.getTimeInUnits() << std::endl;
        std::cout << "Gold on the Castle: " << landscape.getCastleGold() << std::endl;
        for (int i = 0; i < landscape.getFieldSize(); i++){
            for (int j = 0; j < landscape.getFieldSize(); j++){
                if (landscape.getTypeOfField(i, j) == forest){
                    if (landscape.getTypeOfBuilding(i, j) == lair_){
                        std::cout << "|_L_|";
                    }
                    else if (landscape.getTypeOfBuilding(i, j) == castle_){
                        std::cout << "|_C_|";
                    }
                    else{
                        std::cout << "|_F_|";
                    }
                }
                else if (landscape.getTypeOfField(i, j) == road){
                    std::vector<Enemy*> en = landscape.findEnemiesInTheArea(i, j, 0);
                    if (en.empty()){
                        std::cout << "|_R_|";
                    }
                    else {
                        std::cout << "|_" << en.front()->getCurrentHp() << "_|";
                    }
                }
                else if (landscape.getTypeOfField(i, j) == field){
                    if (landscape.getTypeOfBuilding(i, j) == tower_){
                        std::cout << "|_T1_|";
                    }
                    else {
                        std::cout << "|_I_|";
                    }
                }
            }
            std::cout << std::endl;
        }


    }

};


#endif //TOWERDEFENCE_TOWERDEFENCE_H
