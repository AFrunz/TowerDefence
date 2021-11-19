#ifndef TOWERDEFENCE_BUILDING_HPP
#define TOWERDEFENCE_BUILDING_HPP

// 0 - castle
//1 - tower
//2 -

enum BuildingTypes{
    castle_ = 0,
    lair_ = 1,
    tower_ = 2,
    enemy_ = 3,
    trap_ = 4
};

class Building{
public:
    virtual int getType() = 0;
    virtual ~Building() = default;
};


#endif //TOWERDEFENCE_BUILDING_HPP
