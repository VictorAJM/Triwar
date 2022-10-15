#pragma once
#include "Structure.h"

class Mineral : public Structure {
    int gold;
    public:
        Mineral(int _x, int _y): gold(50), Structure(_x, _y, 3,3, 'M',' ') {}
        int GOLD() { return gold;}
};