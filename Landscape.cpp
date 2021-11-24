#include "headers/Landscape.hpp"
#include <cmath>
// Сделать чтение из файла(скорее всего не здесь)
// Подумать над таймером


//private:
//int fieldSize;                                   /// Величина игрового поля
//std::list<Enemy*> enemies;                       /// Позиции врагов
//std::vector<std::vector<Field>> table;           /// Информация об игровом поле

Landscape::Landscape():fieldSize(0), table(), xCastle(-1), yCastle(-1){}

Landscape::Landscape(int n):fieldSize(n), table(n, std::vector<Field>(n)), xCastle(-1), yCastle(-1){}

int Landscape::getFieldSize() const {
    return fieldSize;
}

void Landscape::setFieldSize(int n) {
    if (n < 0) throw std::runtime_error("Negative number\n");
    table = std::vector<std::vector<Field>>(n, std::vector<Field>(n));
    fieldSize = n;
}

int Landscape::getTypeOfField(int x, int y) const{
    if (x >= fieldSize || y >= fieldSize || x < 0 || y < 0) throw std::out_of_range("Wrong cords\n");
    return table[x][y].type;
}

void Landscape::setTypeOfField(int x, int y, int type) {
    if (x >= fieldSize || y >= fieldSize || x < 0 || y < 0) throw std::out_of_range("Wrong cords\n");
    table[x][y].type = type;
}

std::vector<Enemy*> Landscape::findEnemiesInTheArea(int x, int y, int r){
    std::vector<Enemy*> res;

    auto enemyIt = enemies.begin();
    while (enemyIt != enemies.end()){
        if ((*enemyIt)->getCurrentHp() <= 0){
            delete *enemyIt;
            enemyIt = enemies.erase(enemyIt);
            continue;
        }
        int enemyX = (*enemyIt)->getX();
        int enemyY = (*enemyIt)->getY();
        if (std::sqrt((enemyX - x) * (enemyX - x) + (enemyY - y) * (enemyY - y)) / std::sqrt(2) <= r){
            res.push_back(*enemyIt);
        }
        enemyIt++;
    }
    return res;
}

bool Landscape::findRoad(int& x, int& y, int& direction) const{
    bool flag = false;
    if (x >= 0 && x < (fieldSize - 1)) {
        if (table[x + 1][y].type == road && direction != -1) {
            x++;
            direction = 1;
            flag = true;
        }
    }
    if (x <= (fieldSize - 1) && !flag) {
        if (table[x - 1][y].type == road && direction != 1) {
            x--;
            direction = -1;
        }
    }
    if (y >= 0 && y < (fieldSize - 1) && table[x][y + 1].type == road && direction != 2){
        y++;
        direction = -2;
        flag = true;
    }
    if (y <= (fieldSize - 1) && y > 0 && table[x][y - 1].type == road && direction != -2){
        y--;
        direction = 2;
        flag = true;
    }
    return flag;
}

// доделать
int Landscape::updateSituation(int time){
    Castle* castle = dynamic_cast<Castle*>(table[xCastle][yCastle].building);

    bool hasEnemiesInLayers = false;

    for (int i = 0; i < fieldSize; i++){
        for (int j = 0; j < fieldSize; j++){
            if (table[i][j].type == forest || !table[i][j].building) continue;
            if (table[i][j].type == field && table[i][j].building->getType() == tower_){
                Tower* tower = dynamic_cast<Tower*>(table[i][j].building);
                std::vector<Enemy*> enemiesInArea = findEnemiesInTheArea(i, j, tower->getArea());
                for (auto enemy : enemiesInArea){
                    tower->hit(enemy);
                    if (enemy->getCurrentHp() <= 0) castle->increaseGold(*enemy);
                }
            }
            else if (table[i][j].building->getType() == lair_){
                int x = i;
                int y = j;
                int direction = 0;
                findRoad(x, y, direction);
                Lair* lair = dynamic_cast<Lair*>(table[i][j].building);
                hasEnemiesInLayers = hasEnemiesInLayers || lair->hasEnemies();
                Enemy* enemy = lair->releaseEnemy(time);
                if (table[x][y].building && table[x][y].building->getType() == castle_){
                    dynamic_cast<Castle*>(table[x][y].building)->damage(*enemy);
                }
                else if (table[x][y].building && table[x][y].building->getType() == trap_){
                    Trap* trap = dynamic_cast<Trap*>(table[i][j].building);
                    std::vector<Enemy*> enemiesInArea = findEnemiesInTheArea(i, j, trap->getArea());
                    for (auto enemyIter : enemiesInArea){
                        trap->hit(enemy);
                        if (enemy->getCurrentHp() <= 0) castle->increaseGold(*enemy);
                    }
                }
                else {
                    enemy->move(x, y);
                    enemy->setDirection(direction);
                    enemies.push_back(enemy);
                }
            }
        }
    }

    for (auto enemyIter : enemies){
        int x = enemyIter->getX();
        int y = enemyIter->getY();
        int direction = enemyIter->getDirection();
        findRoad(x, y, direction);
        if (table[x][y].building && table[x][y].building->getType() == castle_){
            castle->damage(*enemyIter);
            if (castle->getCurrentHp() <= 0) return -1;
        }
        else {
            if (table[x][y].building && table[x][y].building->getType() == trap_){
                Trap* trap = dynamic_cast<Trap*>(table[x][y].building);
                std::vector<Enemy*> enemiesInArea = findEnemiesInTheArea(x, y, trap->getArea());
                for (auto it : enemiesInArea){
                    trap->hit(it);
                    if (it->getCurrentHp() <= 0) castle->increaseGold(*it);
                }
                delete trap;
                table[x][y].building = nullptr;
            }
        }
    }

    if (!hasEnemiesInLayers && enemies.empty()) return 0;

    return 1;

}

bool Landscape::checkWay(int x, int y) const{
    int direction = 0;
    while (true) {
        if (table[x][y].building && table[x][y].building->getType() == 0) {     // Дошли до замка
            return true;
        }
        if (!findRoad(x, y, direction)) return false;
    }
}

int Landscape::checkCorrect() const {
    if (fieldSize == 0) return 0;
    int castleNumber = 0;
    int lairNumber = 0;
    for (int i = 0; i < fieldSize; i++){
        for (int j = 0; j < fieldSize; j++){
            if (table[i][j].building == nullptr) continue;
            if (table[i][j].building->getType() == castle_){
                castleNumber++;
                if (castleNumber > 1) throw std::runtime_error("Too much castles");
            }
            if (table[i][j].building->getType() == lair_){
                lairNumber++;
                if (!checkWay(i, j)) throw std::runtime_error("No way between layer and castle");
            }
        }
    }
    if (lairNumber == 0) throw std::runtime_error("Have no lairs");
    return 1;
}

int Landscape::setBuilding(Building *building, int x, int y) {
    if (x >= fieldSize || y >= fieldSize || x < 0 || y < 0) throw std::runtime_error("Wrong cords\n");
    if (!building) throw std::runtime_error("Null ptr\n");
    int inputType = building->getType();
    if (inputType == castle_){
        if (xCastle != -1){
            if (x == xCastle && y == yCastle){
                delete table[x][y].building;
                table[x][y].building = building;
                return 0;
            }
            else throw std::runtime_error("Castle already exist\n");
        }
        else throw std::runtime_error("Castle already exist\n");
    }
    else if (inputType == tower_){
        if (table[x][y].type != field) throw std::runtime_error("Wrong place\n");
        if (table[x][y].building) throw std::runtime_error("Place is taken\n");
        table[x][y].building = building;
    }
    else if (inputType == lair_){
        if (table[x][y].building) throw std::runtime_error("Place is taken\n");
        table[x][y].building = building;
    }
    else if (inputType == trap_){
        if (table[x][y].type != road) throw std::runtime_error("Wrong place\n");
        if (table[x][y].building) throw std::runtime_error("Place is taken\n");
        table[x][y].building = building;
    }
    return 0;
}


