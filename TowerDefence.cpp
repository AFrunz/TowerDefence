#include "headers/TowerDefence.h"
#include <unistd.h>

Timer::Timer() {
    timeStart = clock();
    currentTime = timeStart;
    speed = 1;
    units = 0;
}

void Timer::setTimeout(double t) {
    units++;
    double tStart = clock();
    sleep(t);
    currentTime = clock() - timeStart;
}

int Timer::getTimeInUnits() {
    return units;
}


void Timer::setSpeed(double speed_) {
    speed = speed_;
}


