#pragma once
#include "Entity.h"
#include "hitBox.h"
#include "writer.h"
class Unit : public Entity {
    int x,y,speed,health,damage;
    public:
        Unit(int _x, int _y, char _type, char _race): x(_x), y(_y) , Entity(_type, _race) {}
        int SPEED() { return speed;}
        int HEALTH() { return health;}
        int DAMAGE() { return damage;}
        void setSpeed(int _speed) { speed = _speed; }
        void setHealth(int _health) { health = _health; }
        void setDamage(int _damage) { damage = _damage; }
        int X() { return x;}
        int Y() { return y;}
        int setX(int _x) { x = _x;}
        int setY(int _y) { y = _y;}
        hitBox getHitBox() {
            return hitBox(X(),Y(),1,1);
        }
        void paint() {
            gotoXY(X(),Y()); printf("%c",TYPE());
        }
        void erase() {
            gotoXY(X(),Y()); printf(" ");
        }
};