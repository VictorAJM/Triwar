#pragma once
#include "Structure.h"

class Mineral : public Structure {
    int gold;
    int remainedUses;
    public:
        /// @brief 
        /// @param _x 
        /// @param _y 
        Mineral(int _x, int _y):  Structure(_x, _y, 3,3, 'M','d'),gold(10) {
            remainedUses = rand()%4+5;
        }
        int GOLD() { return gold;}
        int getUses() { return remainedUses; }
        void setUses(int _remainedUses) { remainedUses = _remainedUses;}
};