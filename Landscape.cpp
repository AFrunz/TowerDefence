#include "headers/Landscape.hpp"
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

int Landscape::getTypeOfField(int x, int y) {
    if (x >= fieldSize || y >= fieldSize || x < 0 || y < 0) throw std::out_of_range("Wrong cords\n");
    return table[x][y].type;
}

void Landscape::setTypeOfField(int x, int y, int type) {
    if (x >= fieldSize || y >= fieldSize || x < 0 || y < 0) throw std::out_of_range("Wrong cords\n");
    table[x][y].type = type;
}

std::vector<Enemy*> Landscape::findEnemiesInTheArea(int x, int y, int r){
    int leftX = x - r;
    if (leftX < 0) leftX = 0;
    int rightX = x + r;
    if (rightX >= fieldSize) rightX = fieldSize - 1;
    int lowerY = y - r;
    if (lowerY < 0) lowerY = 0;
    int upperY = y + r;
    std::vector<Enemy*> res;
    if (upperY >= fieldSize) upperY = fieldSize - 1;
    for (int i = leftX; i <= rightX; i++){
        for (int j = lowerY; j <= upperY; j++){
            if (table[i][j].type == road){
                if (table[i][j].building && table[i][j].building->getType() == enemy_)
                    res.push_back(dynamic_cast<Enemy*>(table[i][j].building));
            }
        }
    }
    return res;
}

bool Landscape::findRoad(int& x, int& y, int& direction){
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
void Landscape::updateSituation(){
    Castle* castle = dynamic_cast<Castle*>(table[xCastle][yCastle].building);
    for (int i = 0; i < fieldSize; i++){
        for (int j = 0; j < fieldSize; j++){
            if (table[i][j].type == tree || !table[i][j].building) continue;
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
                Enemy* enemy = dynamic_cast<Lair*>(table[i][j].building)->releaseEnemy(0);              ///Поменять время
                if (table[x][y].building && table[x][y].building->getType() == castle_){
                    dynamic_cast<Castle*>(table[x][y].building)->damage(*enemy);
                }
                else {
                    table[x][y].building = enemy;
                    enemy->setDirection(direction);
                }
            }
            else if (table[i][j].building->getType() == enemy_){
                int x = i;
                int y = j;
                Enemy* enemy = dynamic_cast<Enemy*>(table[i][j].building);
                int direction = enemy->getDirection();
                findRoad(x, y, direction);
                if (table[x][y].building && table[x][y].building->getType() == castle_){
                    dynamic_cast<Castle*>(table[x][y].building)->damage(*enemy);
                }
                else {
                    if (table[x][y].building && table[x][y].building->getType() == trap_){
                        Trap* trap = dynamic_cast<Trap*>(table[x][y].building);
                        std::vector<Enemy*> enemies = findEnemiesInTheArea(i, j, trap->getArea());
                        for (auto it : enemies){
                            trap->hit(it);
                            if (it->getCurrentHp() <= 0) castle->increaseGold(*enemy);
                        }
                        delete trap;
                    }
                    table[x][y].building = enemy;
                }
            }
        }
    }
}

bool Landscape::CheckWay(int x, int y){
    int direction = 0;
    while (true) {
        if (table[x][y].building && table[x][y].building->getType() == 0) {     // Дошли до замка
            return true;
        }
        if (!findRoad(x, y, direction)) return false;
    }
}

int Landscape::checkCorrect() {
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
                if (!CheckWay(i, j)) throw std::runtime_error("No way between layer and castle");
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
    else if (inputType == enemy_){
        if (table[x][y].type != road) throw std::runtime_error("Wrong place\n");
        if (table[x][y].building) throw std::runtime_error("Place is taken\n");
        table[x][y].building = building;
    }
    return 0;
}


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
