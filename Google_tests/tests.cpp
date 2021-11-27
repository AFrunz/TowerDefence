#include "gtest//gtest.h"
#include "Trap.hpp"
#include "Castle.hpp"
#include "Spell.hpp"
#include "Enemy.hpp"
#include "Trap.hpp"

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
    Enemy enemy("MyEnemy", 100, 1000, 1, 1, 1, 1);
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
    Enemy enemy("MyEnemy", 100, 10, 15, 1, 3, 1);
    EXPECT_EQ(1, enemy.getX());
    EXPECT_EQ(3, enemy.getY());
    EXPECT_EQ(10, enemy.getGold());
    EXPECT_EQ(100, enemy.getCurrentHp());
    EXPECT_EQ(100, enemy.getMaxHp());
    EXPECT_EQ(1, enemy.getDirection());
    EXPECT_EQ("MyEnemy", enemy.getName());
    EXPECT_EQ(15, enemy.getSpeed());
}

TEST(Enemy, modificators){
    Enemy enemy("MyEnemy", 100, 10, 15, 1, 3, 1);
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