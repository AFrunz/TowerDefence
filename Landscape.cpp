#include "headers/Landscape.hpp"
#include <cmath>


enum answers{
    ST_OK = 0,
    NOT_ENOUGH_MONEY = 1,
    EROR = 2
};


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

bool Landscape::findRoad(int& x, int& y, int& direction) const {
    bool flag = false;
    if (x >= 0 && x < (fieldSize - 1)) {
        if (table[x + 1][y].type == road && direction != -1 ||
        table[x + 1][y].building && table[x + 1][y].building->getType() == castle_) {
            x++;
            direction = 1;
            return true;
        }
    }
    if (x > 0 && x <= (fieldSize - 1)) {
        if (table[x - 1][y].type == road && direction != 1 ||
            table[x - 1][y].building && table[x - 1][y].building->getType() == castle_) {
            x--;
            direction = -1;
            return true;
        }
    }
    if (y >= 0 && y < (fieldSize - 1)){
        if (table[x][y + 1].type == road && direction != 2 ||
        table[x][y + 1].building && table[x][y + 1].building->getType() == castle_) {
            y++;
            direction = -2;
            return true;
        }
    }
    if (y <= (fieldSize - 1) && y > 0) {
        if (table[x][y - 1].type == road && direction != -2 ||
           table[x][y - 1].building && table[x][y - 1].building->getType() == castle_) {
            y--;
            direction = 2;
            return true;
    }
    }
    return false;
    }



int Landscape::updateSituation(int time){
    Castle* castle = dynamic_cast<Castle*>(table[xCastle][yCastle].building);

    bool hasEnemiesInLayers = false;

    for (int i = 0; i < fieldSize; i++){
        for (int j = 0; j < fieldSize; j++){
            if (!table[i][j].building) continue;
            if (table[i][j].type == field && table[i][j].building->getType() == tower_){
                Tower* tower = dynamic_cast<Tower*>(table[i][j].building);
                std::vector<Enemy*> enemiesInArea = findEnemiesInTheArea(i, j, tower->getArea());
                if (!enemiesInArea.empty()){
                    auto enemy = std::min_element(enemiesInArea.begin(), enemiesInArea.end(), [i, j](auto first, auto second){

                        return (first->getX() - i) * (first->getX() - i) + (first->getY() - j) * (first->getY()) <
                               (second->getX() - i) * (second->getX() - i) + (second->getY() - j) * (second->getY());

                    });
                    tower->hit(*enemy);
                    if ((*enemy)->getCurrentHp() <= 0) castle->increaseGold(**enemy);
                }
            }
            else if (table[i][j].building->getType() == lair_){
                int x = i;
                int y = j;
                int direction = 0;
                findRoad(x, y, direction);
                std::cout << "Enemy in lair:" << x << y << direction << std::endl;
                Lair* lair = dynamic_cast<Lair*>(table[i][j].building);
                hasEnemiesInLayers = hasEnemiesInLayers || lair->hasEnemies();
                Enemy* enemy = lair->releaseEnemy(time);
                if (!enemy) continue;
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
                    enemy->move(x, y, direction, fieldSize);
                    enemies.push_back(enemy);
                }
            }
        }
    }

    auto enemyIter = enemies.begin();
    while (enemyIter != enemies.end()){
        (*enemyIter)->takeDamageFromPoison();
        (*enemyIter)->decreaseSpellTime();
        if ((*enemyIter)->getCurrentHp() <= 0){
            castle->increaseGold(**enemyIter);
            delete (*enemyIter);
            enemyIter = enemies.erase(enemyIter);
            continue;
        }
        enemyIter++;
    }

    if (!hasEnemiesInLayers && enemies.empty()) return 1;
    return 0;

}


// Движение дискретное, нет учета зелий
int Landscape::updateEnemiesPosition(){
    Castle *castle = dynamic_cast<Castle*>(table[xCastle][yCastle].building);
    auto enemyIter = enemies.begin();
    while (enemyIter != enemies.end()){

        int x = (*enemyIter)->getX();
        int y = (*enemyIter)->getY();
        int direction = (*enemyIter)->getDirection();
        findRoad(x, y, direction);
        if (table[x][y].building && table[x][y].building->getType() == castle_){
            castle->damage(**enemyIter);
            delete *enemyIter;
            enemyIter = enemies.erase(enemyIter);
            if (castle->getCurrentHp() <= 0) return 1;
            continue;
        }
        else {
            if (table[x][y].building && table[x][y].building->getType() == trap_){
                Trap* trap = dynamic_cast<Trap*>(table[x][y].building);
                std::vector<Enemy*> enemiesInArea = findEnemiesInTheArea(x, y, trap->getArea());
                for (auto it : enemiesInArea){
                    trap->hit(it);
//                    if (it->getCurrentHp() <= 0) castle->increaseGold(*it);
                }
                delete trap;
                table[x][y].building = nullptr;
            }
            (*enemyIter)->move(x, y, direction, fieldSize);
        }
        enemyIter++;
    }
    if (enemies.empty()) return -1;
    return 0;
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

void Landscape::setBuilding(Building *building, int x, int y) {
    if (x >= fieldSize || y >= fieldSize || x < 0 || y < 0) throw std::runtime_error("Wrong cords\n");
    if (!building) throw std::runtime_error("Null ptr\n");
    int inputType = building->getType();
    if (inputType == castle_){
        if (xCastle != -1){
            if (x == xCastle && y == yCastle){
                delete table[x][y].building;
                table[x][y].building = building;
                return;
            }
            else throw std::runtime_error("Castle already exist\n");
        }
        else {
            table[x][y].building = building;
            xCastle = x;
            yCastle = y;
            return;
        }
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
}

int Landscape::getTypeOfBuilding(int x, int y) const{
    if (!table[x][y].building) return -1;
    return table[x][y].building->getType();
}

int Landscape::getCastleGold() const{
    Castle* castle = dynamic_cast<Castle*>(table[xCastle][yCastle].building);
    return castle->getGold();
}

void Landscape::decreaseCastleGold(int gold){
    Castle* castle = dynamic_cast<Castle*>(table[xCastle][yCastle].building);
    castle->decreaseGold(gold);
}

int Landscape::towerUp(int x, int y) {
    if (!table[x][y].building) return EROR;
    if (table[x][y].building->getType() == tower_){
        Tower* tower = dynamic_cast<Tower*>(table[x][y].building);
        if (tower->getTowerType() == basic_ && getCastleGold() >= BaseTower::getPrice(tower->getLvl())){
            int result = tower->lvlUp();
            if (!result) decreaseCastleGold(BaseTower::getPrice(tower->getLvl() + 1));
        }
        else if (tower->getType() == magic_ && getCastleGold() >= MagicTower::getPrice(tower->getLvl())){
            int result = tower->lvlUp();
            if (!result) decreaseCastleGold(BaseTower::getPrice(tower->getLvl() + 1));
        }
        else return NOT_ENOUGH_MONEY;
    }
    else return EROR;
    return ST_OK;
}

int Landscape::getCastleHealth() const{
    Castle* castle = dynamic_cast<Castle*>(table[xCastle][yCastle].building);
    return castle->getCurrentHp();
}

Landscape::~Landscape() {
    for (auto it = enemies.begin(); it != enemies.end(); it++){
        delete *it;
    }
    for (auto it = table.begin(); it != table.end(); it++){
        for (auto it1 = it->begin(); it1 != it->end(); it1++){
            delete it1->building;
        }
    }
}



