#ifndef TOWERDEFENCE_SETTINGS_H
#define TOWERDEFENCE_SETTINGS_H

//TextureLoader

const float WINDOW_WIDTH = 1600;
const float WINDOW_HEIGHT = 900;

//const float WINDOW_WIDTH = 1920;
//const float WINDOW_HEIGHT = 1080;

const float MAP_OFFSET_X = WINDOW_WIDTH * 0.07;
const float MAP_OFFSET_Y = WINDOW_HEIGHT * 0.2;
const float MAP_SIZE = WINDOW_HEIGHT / 2;

const float INTERFACE_OFFSET_X = WINDOW_WIDTH * 0.5;
const float INTERFACE_OFFSET_Y = MAP_OFFSET_Y;

const float TIMER_OFFSET_X = WINDOW_WIDTH * 0.07;
const float TIMER_OFFSET_Y = WINDOW_HEIGHT * 0.02;

const float GOLD_OFFSET_X = WINDOW_WIDTH * 0.07;
const float GOLD_OFFSET_Y = TIMER_OFFSET_Y + 50;

const float HEALTH_OFFSET_X = WINDOW_WIDTH * 0.07;
const float HEALTH_OFFSET_Y = GOLD_OFFSET_Y + 50;

//const float MAP_HEIGHT = WINDOW_WIDTH / 2;




//Trap
const int TRAP_TIME = 2;
const int TRAP_RADIUS = 2;
const int TRAP_PRICE = 10;
//Spell

const int POISONING_SPELL_TIME = 2;
const int DEBILITATION_SPELL_TIME = 2;
const int SLOWING_SPELL_TIME = 2;
const int POISONING_SPELL_POWER = 5;
const int DEBILITATION_SPELL_POWER = 100;
const int SLOWING_SPELL_POWER = 0;

//file paths

const std::string castleFileName = "/mnt/c/Users/frunz/Desktop/c_or_c++/TowerDefenceV2/settingFiles/castle.txt";
const std::string mapFileName = "/mnt/c/Users/frunz/Desktop/c_or_c++/TowerDefenceV2/settingFiles/map.txt";
const std::string lairFileName = "/mnt/c/Users/frunz/Desktop/c_or_c++/TowerDefenceV2/settingFiles/lair.txt";
const std::string logFileName = "/mnt/c/Users/frunz/Desktop/c_or_c++/TowerDefenceV2/settingFiles/log.txt";


//Tower


const int MAX_LVL_OF_BASE_TOWER = 2;
const int MAX_LVL_OF_MAGIC_TOWER = 2;

//Enemy

const std::string ENEMY_TEXTURE_PATH = "bin/content/textures/Enemy.png";


#endif //TOWERDEFENCE_SETTINGS_H
