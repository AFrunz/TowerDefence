#ifndef TOWERDEFENCE_CASTLE_HPP
#define TOWERDEFENCE_CASTLE_HPP

#include "Building.hpp"
#include "Enemy.hpp"
#include "string"

///Замок
class Castle:public Building{

private:
    std::string name;           ///< Имя замка
    int maxHp;                  ///< Максимальное здоровье
    int currentHp;              ///< Текущее здоровье
    int gold;                   ///< Золото

public:
    Castle();
    Castle(std::string name, int maxHealthPoint, int startGold);
    int getType() const;                            ///< Получение типа
    int getGold() const;                            ///< Получение количества золота
    int getMaxHp() const;                           ///< Получение максимальной прочности замка
    int getCurrentHp() const;                       ///< Получение текущей прочности замка
    std::string getName() const;                    ///< Получение имени замка
    void damage(const Enemy& enemy);                ///< "Ударить" замок
    void increaseGold(const Enemy& enemy);          ///< Добавить золота в казну
    void decreaseGold(int gold_);
    virtual ~Castle() = default;
};



#endif //TOWERDEFENCE_CASTLE_HPP
