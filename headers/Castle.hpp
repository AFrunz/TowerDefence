#ifndef TOWERDEFENCE_CASTLE_HPP
#define TOWERDEFENCE_CASTLE_HPP

#include "Building.hpp"
#include "Enemy.hpp"
#include "string"

///Замок
class Castle:public Building{

private:
    std::string name;           /// Имя замка
    int maxHp;                  /// Максимальное здоровье
    int currentHp;              /// Текущее здоровье
    int gold;                   /// Золото

public:
    Castle();
    Castle(std::string name, int maxHealthPoint, int startGold);
    int getGold() const;
    int getMaxHp() const;
    int getCurrentHp() const;
    std::string getName() const;
    void damage(const Enemy& enemy);               /// "Ударить" замок
    void increaseGold(const Enemy& enemy);         /// Добавить золота в казну
    virtual ~Castle() = default;
};



#endif //TOWERDEFENCE_CASTLE_HPP
