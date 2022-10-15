#pragma once
#include "consts.h"

class Entity {
    char type;
    char race;
    public:
        Entity(char _type, char _race): type(_type), race(_race) {}
        char TYPE() { return type;}
        char RACE() { return race;}      
};