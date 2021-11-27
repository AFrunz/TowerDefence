#include <iostream>
/// Tower settings

class TowerFeature{
public:
    int damage;
    int radius;
    int price;
};


const TowerFeature TowerLVL[] = {{1, 1, 100}, {1, 2, 200}, {2, 3, 500}};


/// Map settings

//L - layer
//F - forest
//R - road
//C - castle
//I - field

const std::string mapSettings("4LRRFRIRRRRIRFRRC");



