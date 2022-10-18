#pragma once
#include "Structure.h"

class Base : public Structure {
    /// @brief 
    int gold;
    public:
        /// @brief 
        /// @param _x 
        /// @param _y 
        /// @param _race 
        Base(int _x, int _y, char _race): Structure(_x, _y, 10, 10, 'B', _race) {
            gold = 0;
        }
        int GOLD() { return gold; }
        void addGold(int _gold) { gold += _gold; return; }
};