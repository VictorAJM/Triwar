#pragma once
#include "Structure.h"

class Mineral : public Structure {
    int gold;
    public:
        /// @brief 
        /// @param _x 
        /// @param _y 
        Mineral(int _x, int _y):  Structure(_x, _y, 3,3, 'M',' '),gold(50) {}
        int GOLD() { return gold;}
};