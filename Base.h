#pragma once
#include "Structure.h"

class Base : public Structure {
    int gold;
    public:
        Base(int _x, int _y, char _race): gold(0), Structure(_x, _y, 10, 10, 'B', _race) {}
        int GOLD() { return gold; }
};