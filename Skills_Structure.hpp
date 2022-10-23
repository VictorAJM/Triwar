#pragma once
#include "Structure.h"


class Skills_Structure : public Structure {
    int skill;
    int cooldown;
    public:
        Skills_Structure(int _x, int _y, char _race) :  Structure(_x, _y, 2,2, 'R',_race) {
            skill = rand()%2;
            cooldown = COOLDOWN_GENERATOR;
            // health, damage
        }
        int SKILL() { return skill;}
        int CD() { return cooldown; }
        void setCD(int _cooldown) { cooldown = _cooldown; }
        void setSkill() { skill = rand()%2; }
};