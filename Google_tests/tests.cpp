#include <fstream>
#include "gtest//gtest.h"
#include "Trap.hpp"
#include "Castle.hpp"
#include "Spell.hpp"
#include "Enemy.hpp"
#include "Tower.hpp"
#include "Lair.hpp"
#include "TowerDefence.h"
#include "list.hpp"

/// Castle

TEST(Castle, constructors){
    Castle castle;
    EXPECT_EQ(0, castle.getMaxHp());
    EXPECT_EQ(0, castle.getCurrentHp());
    EXPECT_EQ(0, castle.getGold());
}

TEST(Castle, getters){
    Castle castle("MyCastle", 1000, 100);
    EXPECT_EQ(100, castle.getGold());
    EXPECT_EQ(0, castle.getType());
    EXPECT_EQ(1000, castle.getMaxHp());
    EXPECT_EQ(1000, castle.getCurrentHp());
    EXPECT_EQ("MyCastle", castle.getName());
}

TEST(Castle, damage_increaseGold){
    Castle castle("MyCastle", 1000, 100);
    Enemy enemy("MyEnemy", 100, 1000, 1);
    castle.damage(enemy);
    EXPECT_EQ(900, castle.getCurrentHp());
    EXPECT_EQ(100, castle.getGold());
    castle.increaseGold(enemy);
    EXPECT_EQ(1100, castle.getGold());
}


/// Spell

TEST(SlowingSpell, getters){
    SlowingSpell spellVoid;
    EXPECT_EQ(1, spellVoid.getType());
    EXPECT_EQ(0, spellVoid.getTime());
    EXPECT_EQ(0, spellVoid.getPower());

    SlowingSpell spell(12, 123);
    EXPECT_EQ(1, spell.getType());
    EXPECT_EQ(12, spell.getTime());
    EXPECT_EQ(123, spell.getPower());
}

TEST(PoisoningSpell, getters){
    PoisoningSpell spellVoid;
    EXPECT_EQ(2, spellVoid.getType());
    EXPECT_EQ(0, spellVoid.getTime());
    EXPECT_EQ(0, spellVoid.getPower());

    PoisoningSpell spell(12, 123);
    EXPECT_EQ(2, spell.getType());
    EXPECT_EQ(12, spell.getTime());
    EXPECT_EQ(123, spell.getPower());
}

TEST(DebilitationSpell, getters){
    DebilitationSpell spellVoid;
    EXPECT_EQ(3, spellVoid.getType());
    EXPECT_EQ(0, spellVoid.getTime());
    EXPECT_EQ(0, spellVoid.getPower());

    DebilitationSpell spell(12, 123);
    EXPECT_EQ(3, spell.getType());
    EXPECT_EQ(12, spell.getTime());
    EXPECT_EQ(123, spell.getPower());
}


/// Enemy

TEST(Enemy, gettersVoid){
    Enemy enemyVoid;
    EXPECT_EQ(-1, enemyVoid.getX());
    EXPECT_EQ(-1, enemyVoid.getY());
    EXPECT_EQ(0, enemyVoid.getGold());
    EXPECT_EQ(0, enemyVoid.getCurrentHp());
    EXPECT_EQ(0, enemyVoid.getMaxHp());
    EXPECT_EQ(0, enemyVoid.getDirection());
    EXPECT_EQ("", enemyVoid.getName());
    EXPECT_EQ(0, enemyVoid.getSpeed());
}

TEST(Enemy, getters){
    Enemy enemy("MyEnemy", 100, 10, 15);
    EXPECT_EQ(-1, enemy.getX());
    EXPECT_EQ(-1, enemy.getY());
    EXPECT_EQ(10, enemy.getGold());
    EXPECT_EQ(100, enemy.getCurrentHp());
    EXPECT_EQ(100, enemy.getMaxHp());
    EXPECT_EQ(0, enemy.getDirection());
    EXPECT_EQ("MyEnemy", enemy.getName());
    EXPECT_EQ(15, enemy.getSpeed());
}

TEST(Enemy, modificators){
    Enemy enemy("MyEnemy", 100, 10, 15);
    enemy.move(4, 8, -2);
    EXPECT_EQ(4, enemy.getX());
    EXPECT_EQ(8, enemy.getY());
    EXPECT_EQ(10, enemy.getGold());
    EXPECT_EQ(100, enemy.getCurrentHp());
    EXPECT_EQ(100, enemy.getMaxHp());
    EXPECT_EQ(-2, enemy.getDirection());
    EXPECT_EQ("MyEnemy", enemy.getName());
    EXPECT_EQ(15, enemy.getSpeed());
    enemy.reduceHp(10);
    EXPECT_EQ(4, enemy.getX());
    EXPECT_EQ(8, enemy.getY());
    EXPECT_EQ(10, enemy.getGold());
    EXPECT_EQ(90, enemy.getCurrentHp());
    EXPECT_EQ(100, enemy.getMaxHp());
    EXPECT_EQ(-2, enemy.getDirection());
    EXPECT_EQ("MyEnemy", enemy.getName());
    EXPECT_EQ(15, enemy.getSpeed());
}


/// Trap

TEST(Trap, getters){
    Trap trapVoid;
    DebilitationSpell spell(12, 1);
    Trap trap(&spell, 3);

    EXPECT_EQ(4, trapVoid.getType());
    EXPECT_EQ(0, trapVoid.getArea());

    EXPECT_EQ(4, trap.getType());
    EXPECT_EQ(3, trap.getArea());
}


TEST(Trap, modificators){
    DebilitationSpell spell(12, 1);
    Trap trap(&spell, 3);
    Enemy enemy("MyEnemy", 100, 10, 15);
    trap.hit(&enemy);
    EXPECT_EQ(-1, enemy.getX());
    EXPECT_EQ(-1, enemy.getY());
    EXPECT_EQ(10, enemy.getGold());
    EXPECT_EQ(100, enemy.getCurrentHp());
    EXPECT_EQ(100, enemy.getMaxHp());
    EXPECT_EQ(0, enemy.getDirection());
    EXPECT_EQ("MyEnemy", enemy.getName());
    EXPECT_EQ(15, enemy.getSpeed());
}


/// Tower

TEST(BaseTower, allMethods){
    BaseTower tower;
    EXPECT_EQ(0, tower.getLvl());
    EXPECT_EQ(2, tower.getType());
    EXPECT_EQ(BaseTowerLVL[0].radius, tower.getArea());
    tower.lvlUp();
    EXPECT_EQ(1, tower.getLvl());
    EXPECT_EQ(BaseTowerLVL[1].radius, tower.getArea());
    EXPECT_EQ(2, tower.getType());
    tower.lvlUp();
    EXPECT_EQ(2, tower.getLvl());
    EXPECT_EQ(BaseTowerLVL[2].radius, tower.getArea());
    EXPECT_EQ(2, tower.getType());
    tower.lvlUp();
    EXPECT_EQ(2, tower.getLvl());
    EXPECT_EQ(BaseTowerLVL[2].radius, tower.getArea());
    EXPECT_EQ(2, tower.getType());
    Enemy enemy("MyEnemy", 100, 10, 15);
    tower.hit(&enemy);
    EXPECT_EQ(100 - BaseTowerLVL[2].damage, enemy.getCurrentHp());
    EXPECT_EQ(100, enemy.getMaxHp());


}


TEST(MagicTower, allMethods){
    MagicTower tower;
    EXPECT_EQ(0, tower.getLvl());
    EXPECT_EQ(2, tower.getType());
    EXPECT_EQ(MagicTowerLVL[0].radius, tower.getArea());
    tower.lvlUp();
    EXPECT_EQ(1, tower.getLvl());
    EXPECT_EQ(MagicTowerLVL[1].radius, tower.getArea());
    EXPECT_EQ(2, tower.getType());
    tower.lvlUp();
    EXPECT_EQ(2, tower.getLvl());
    EXPECT_EQ(MagicTowerLVL[2].radius, tower.getArea());
    EXPECT_EQ(2, tower.getType());
    tower.lvlUp();
    EXPECT_EQ(2, tower.getLvl());
    EXPECT_EQ(MagicTowerLVL[2].radius, tower.getArea());
    EXPECT_EQ(2, tower.getType());
    Enemy enemy("MyEnemy", 100, 10, 15);
    tower.hit(&enemy);
    EXPECT_EQ(100 - MagicTowerLVL[2].damage, enemy.getCurrentHp());
    EXPECT_EQ(100, enemy.getMaxHp());
}


/// Lair

TEST(Lair, allMethods){
    Lair lair;
    EnemyTime enemy1("MyEnemy1", 100, 10, 15, 3);
    EnemyTime enemy2("MyEnemy2", 100, 10, 15, 5);
    EnemyTime enemy3("MyEnemy3", 100, 10, 15, 1);
    EnemyTime enemy4("MyEnemy4", 100, 10, 15, 6);
    EnemyTime enemy5("MyEnemy5", 100, 10, 15, 4);
    EXPECT_EQ(1, lair.getType());
    EXPECT_EQ(false, lair.hasEnemies());
    lair.pushEnemy(enemy1);
    lair.pushEnemy(enemy2);
    lair.pushEnemy(enemy3);
    lair.pushEnemy(enemy4);
    lair.pushEnemy(enemy5);
    EXPECT_EQ(true, lair.hasEnemies());
    EXPECT_EQ("MyEnemy3", lair.releaseEnemy(1)->getName());
    EXPECT_EQ("MyEnemy1", lair.releaseEnemy(3)->getName());
    EXPECT_EQ(nullptr, lair.releaseEnemy(1));
}


/// TowerDefence

const std::string castleFileName = "/mnt/c/Users/frunz/Desktop/c_or_c++/TowerDefence/settingFiles/castle.txt";
const std::string mapFileName = "/mnt/c/Users/frunz/Desktop/c_or_c++/TowerDefence/settingFiles/map.txt";
const std::string lairFileName = "/mnt/c/Users/frunz/Desktop/c_or_c++/TowerDefence/settingFiles/lair.txt";


TEST(TowerDefence, inputCastleFromFile){
    std::ifstream castleStream(castleFileName);
    EXPECT_EQ(1, castleStream.is_open());
    TowerDefence td;
    Castle* castle = td.loadCastle(castleStream);
    castleStream.close();
    if (castle){
        EXPECT_EQ("MyCastle", castle->getName());
        EXPECT_EQ(100, castle->getMaxHp());
        EXPECT_EQ(1000, castle->getGold());
    }
    else {
        EXPECT_EQ(1, 0);
    }
    delete castle;
}



TEST(TowerDefence, inputLairFromFile){
    std::ifstream lairStream(lairFileName);
    EXPECT_EQ(1, lairStream.is_open());
    TowerDefence td;
    Lair* lair = td.loadLair(lairStream);
    EXPECT_EQ(true, lair->hasEnemies());

    Enemy* enemy = lair->releaseEnemy(0);
    EXPECT_EQ("Enemy1", enemy->getName());
    EXPECT_EQ(10, enemy->getMaxHp());
    EXPECT_EQ(15, enemy->getGold());
    EXPECT_EQ(1, enemy->getSpeed());
    delete enemy;

    enemy = lair->releaseEnemy(1);
    EXPECT_EQ("Enemy4", enemy->getName());
    EXPECT_EQ(10, enemy->getMaxHp());
    EXPECT_EQ(15, enemy->getGold());
    EXPECT_EQ(1, enemy->getSpeed());
    delete enemy;

    enemy = lair->releaseEnemy(2);
    EXPECT_EQ("Enemy2", enemy->getName());
    EXPECT_EQ(10, enemy->getMaxHp());
    EXPECT_EQ(15, enemy->getGold());
    EXPECT_EQ(1, enemy->getSpeed());
    delete enemy;

    enemy = lair->releaseEnemy(3);
    EXPECT_EQ("Enemy3", enemy->getName());
    EXPECT_EQ(10, enemy->getMaxHp());
    EXPECT_EQ(15, enemy->getGold());
    EXPECT_EQ(1, enemy->getSpeed());
    delete enemy;

    enemy = lair->releaseEnemy(7);
    EXPECT_EQ("Enemy5", enemy->getName());
    EXPECT_EQ(10, enemy->getMaxHp());
    EXPECT_EQ(15, enemy->getGold());
    EXPECT_EQ(1, enemy->getSpeed());
    delete enemy;


    lairStream.close();
    delete lair;
}


TEST(TowerDefence, inputMapFromFile){
    int status[] = {forest, road, field, forest, field, road, road, field, field, field, road, road, forest, field, forest, forest};
    std::ifstream lairStream(lairFileName);
    EXPECT_EQ(1, lairStream.is_open());
    std::ifstream castleStream(castleFileName);
    EXPECT_EQ(1, castleStream.is_open());
    std::ifstream mapStream(mapFileName);
    EXPECT_EQ(1, mapStream.is_open());

    TowerDefence td;
    td.loadMap(mapStream, castleStream, lairStream);
    Landscape landscape = td.getLandscapeCopy();
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            EXPECT_EQ(status[4 * i + j], landscape.getTypeOfField(i, j));
        }
    }

}

TEST(TowerDefence, stratGame){

    std::ifstream lairStream(lairFileName);
    EXPECT_EQ(1, lairStream.is_open());
    std::ifstream castleStream(castleFileName);
    EXPECT_EQ(1, castleStream.is_open());
    std::ifstream mapStream(mapFileName);
    EXPECT_EQ(1, mapStream.is_open());

    TowerDefence td;
    td.loadMap(mapStream, castleStream, lairStream);
    td.startGame();
}




TEST(list, standard){
    list<int> li;
    li.push_back(12);
    li.push_front(1);
    EXPECT_EQ(1, li.front());
    EXPECT_EQ(12, li.back());
    li.pop_front();
    EXPECT_EQ(12, li.front());
    EXPECT_EQ(12, li.back());
    li.pop_front();
    EXPECT_ANY_THROW(li.back());
    EXPECT_EQ(true, li.empty());
    li.push_back(12);
    li.push_front(1);
    li.push_back(3);
    li.push_back(5);
    li.push_back(2);
    li.push_back(7);
    li.push_back(1);
    li.sort([](int a, int b)->bool{
        return a < b;
    });

    list<int>::iterator it = li.begin();
    EXPECT_EQ(1, *it);
    EXPECT_EQ(1, *(++it));
    EXPECT_EQ(2, *(++it));
    EXPECT_EQ(3, *(++it));
    EXPECT_EQ(5, *(++it));
    EXPECT_EQ(7, *(++it));
    EXPECT_EQ(12, *(++it));



}



//TEST(TowerDefence, startGame){
//    std::ifstream lairStream(lairFileName);
//    EXPECT_EQ(1, lairStream.is_open());
//    std::ifstream castleStream(castleFileName);
//    EXPECT_EQ(1, castleStream.is_open());
//    std::ifstream mapStream(mapFileName);
//    EXPECT_EQ(1, mapStream.is_open());
//
//    TowerDefence td;
//    td.loadMap(mapStream, castleStream, lairStream);
//    td.startGame();
//}





//TEST(Castle, getgold){
//
//}
//TEST(Castle, getgold){
//
//}
//TEST(Castle, getgold){
//
//}
//TEST(Castle, getgold){
//
//}
//TEST(Castle, getgold){
//
//}
//TEST(Castle, getgold){
//
//}
//TEST(Castle, getgold){
//
//}


int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}