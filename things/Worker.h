#pragma once
#include "Unit.h"

class Worker : public Unit {
    int gold;
    public:
        /// @brief 
        /// @param _x 
        /// @param _y 
        /// @param _race 
        Worker(int _x, int _y, char _race):  Unit(_x, _y, 'W', _race), gold(0) {}
        int GOLD() { return gold; }
        void setGold(int _gold) { gold = _gold; return;}
};