#pragma once
#include "Unit.h"

class Worker : public Unit {
    int gold;
    public:
        Worker(int _x, int _y, char _race): gold(0), Unit(_x, _y, 'W', _race) {}
        int GOLD() { return gold; }
        int setGold(int _gold) { gold = _gold; }
};