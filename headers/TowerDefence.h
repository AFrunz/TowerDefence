#ifndef TOWERDEFENCE_TOWERDEFENCE_H
#define TOWERDEFENCE_TOWERDEFENCE_H
#include "Landscape.hpp"

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



class TowerDefence {
private:
    Landscape landscape;
    Timer timer;
public:
    int startGame(){
        int status = landscape.updateSituation(timer.getTimeInUnits());
        if (status == 0) return 0;
        this->startGame();
    }

};


#endif //TOWERDEFENCE_TOWERDEFENCE_H
