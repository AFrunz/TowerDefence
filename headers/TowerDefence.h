#ifndef TOWERDEFENCE_TOWERDEFENCE_H
#define TOWERDEFENCE_TOWERDEFENCE_H
#include "Landscape.hpp"
#include <map>
class Timer{
private:
    double timeStart;
    double currentTime;
    double speed;
    int units;
public:
    Timer();
    int getTimeInUnits();
    void setTimeout(double t);
    void setSpeed(double speed_ = 1);
};

///// Побочный класс для хранения сведений о клетке поля
//struct Field{
//    int type;
//    Building* building;
//    Field():type(0), building(nullptr){};
//    Field(int type_, Building* building_):type(type_), building(building_){};
//};
//
///// Типы клеток(убрать)
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






class TowerDefence {
private:
    Landscape landscape;
    Timer timer;
public:
    TowerDefence():landscape(), timer(){};

    Landscape getLandscapeCopy(){return landscape;};

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


///
    int startGame(){
        int status = landscape.updateSituation(timer.getTimeInUnits());
        if (status == 0) return 0;
        status = this->startGame();
        return status;
    }

};


#endif //TOWERDEFENCE_TOWERDEFENCE_H
