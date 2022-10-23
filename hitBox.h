#pragma once
#include "consts.h"

struct hitBox {
    int x,y,w,h;
    hitBox(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {}
    hitBox()  {x=y=w=h=1;}
    bool collisionWith(const hitBox other)
    {
        if (x+w<=other.x || x>=other.x+other.w) return false;
        if (y+h<=other.y || y>=other.y+other.h) return false;
        return true;
    }
    bool shareSide(const hitBox other)
    {
        if (this->collisionWith(other)) return false;
        if (other.y<=y && y<other.y+other.h) {
            if (x==other.x+other.w || x+w==other.x) return true;    
        }
        if (other.x<=x && x<other.x+other.w) {
            if (y==other.y+other.h || y+h==other.y) return true;
        }
        return false;
    }
};