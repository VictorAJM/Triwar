#pragma once
#include "Unit.h"

class Kamikaze : public Unit {
    public:
        Kamikaze(int _x, int _y, char _race): Unit(_x, _y, 'K', _race) {
            setDamage(0);
            setHealth(200);
        }
};