#pragma once
#include "Entity.h"
#include "hitBox.h"
#include "writer.h"
class Unit : public Entity {
    int x,y,speed,health,damage;
    public:
        Unit(int _x, int _y, char _type, char _race): Entity(_type, _race), x(_x), y(_y)  {
            health = 50;
            damage = 10;
        }
        int SPEED() { return speed;}
        int HEALTH() { return health;}
        int DAMAGE() { return damage;}
        void setSpeed(int _speed) { speed = _speed; }
        void setHealth(int _health) { health = _health; }
        void setDamage(int _damage) { damage = _damage; }
        int X() { return x;}
        int Y() { return y;}
        void setX(int _x) { x = _x;}
        void setY(int _y) { y = _y;}
        hitBox getHitBox() {
            return hitBox(X(),Y(),1,1);
        }
        void paint() {
            gotoXY(X(),Y()); 
            printw("%c",TYPE());
            refresh();
            //cout << colors[this->RACE()-'a'] << TYPE()<<colors[4];
        }
        void erase() {
            gotoXY(X(),Y()); printw(" ");
            refresh();
        }
        string getInfo()
        {
            string info = "";
            info.push_back(TYPE());
            info.push_back(' ');
            info.push_back(RACE());
            info.push_back(' ');
            info += to_string(X());
            info.push_back(' ');
            info += to_string(Y());
            info.push_back(' ');
            info += to_string(HEALTH());
            info.push_back(' ');
            info += to_string(DAMAGE());
            return info;
        }
};