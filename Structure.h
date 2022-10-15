#pragma once
#include "Entity.h"
#include "writer.h"
class Structure : Entity {
    int x,y,w,h;
    public:
        Structure(int _x, int _y, int _w, int _h, char _type, char _race): x(_x), y(_y), w(_w), h(_h), Entity(_type, _race) {}
        int X() { return x;}
        int Y() { return y;}
        int W() { return w;}
        int H() { return h;}
        void paint() {
            for (int i=X();i<X()+W();i++) {
                for (int j=Y();j<Y()+H();j++) {
                    gotoXY(i,j);
                    printf("%c",TYPE());
                }
            }
        }
        void erase() {
            for (int i=X();i<X()+W();i++) {
                for (int j=Y();j<Y()+H();j++) {
                    gotoXY(i,j);
                    printf(" ");
                }
            }
        }
};