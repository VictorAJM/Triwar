#pragma once
#include "consts.h"
#include "Structure.h"
#include "Worker.h"
#include "Soldier.h"
//#include "Area_Random.hpp"
class Worker_Generator : public Structure {
    int cooldown;
    public:
        Worker_Generator(int _x, int _y, char _race):  Structure(_x, _y, 5,5, 'Q',_race),cooldown(50) {}
        int CD() { return cooldown; }
        void setCD(int _cooldown) { cooldown = _cooldown; }
};

class Soldier_Generator : public Structure {
    int cooldown;
    public:
        Soldier_Generator(int _x, int _y, char _race): Structure(_x,_y,5,5,'E',_race), cooldown(50) {}
        int CD() { return cooldown; }
        void setCD(int _cooldown) { cooldown = _cooldown;}
};