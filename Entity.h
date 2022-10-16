#pragma once
#include "consts.h"

class Entity {
    char type;
    char race;
    int id;
    public:
        Entity(char _type, char _race): type(_type), race(_race) {
            do {
                id = rand();
            } while (entitiesID.count(id)>0);
            entitiesID.insert(id);
        }
        char TYPE() { return type;}
        char RACE() { return race;}      
};