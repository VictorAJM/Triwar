#pragma once

class Soldier : public Unit {
    public:
        Soldier(int _x, int _y, char _race): Unit(_x, _y, 'S', _race) {}
};