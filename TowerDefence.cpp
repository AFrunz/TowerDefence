#include "headers/TowerDefence.h"


Timer::Timer() {
    timeStart = clock();
    currentTime = timeStart;
    speed = 1;
}

void Timer::setTimeout(double t) {
    double tStart = clock();
    while ((clock() - currentTime) / CLOCKS_PER_SEC < (t / speed)){

    }
    currentTime = clock() - timeStart;
}

void Timer::setSpeed(double speed_) {
    speed = speed_;
}


