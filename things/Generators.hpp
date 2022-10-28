#pragma once
#include "Structure.h"
#include "Worker.h"
#include "Soldier.h"
class Worker_Generator : public Structure {
    int cooldown;
    int h,d;
    public:
        Worker_Generator(int _x, int _y, char _race):  Structure(_x, _y, 5,5, 'Q',_race),cooldown(COOLDOWN_GENERATOR) {
            h=d=0;
        }
        void addHealth(int _h) { h += _h;} 
        void addDamage(int _d) { d += _d;}
        int getHealth() { return h;}
        int getDamage() { return d;}
        int CD() { return cooldown; }
        void setCD(int _cooldown) { cooldown = _cooldown; }
};

class Soldier_Generator : public Structure {
    int cooldown;
    int h,d;
    public:
        Soldier_Generator(int _x, int _y, char _race): Structure(_x,_y,5,5,'E',_race), cooldown(COOLDOWN_GENERATOR) {
            h=d=0;
        }
        void addHealth(int _h) { h += _h;} 
        void addDamage(int _d) { d += _d;}
        int getHealth() { return h;}
        int getDamage() { return d;}
        int CD() { return cooldown; }
        void setCD(int _cooldown) { cooldown = _cooldown;}
};