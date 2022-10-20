#pragma once
#include "Entity.h"
#include "writer.h"
#include "hitBox.h"
class Structure : public Entity {
    int x,y,w,h;
    public:
        /// @brief 
        /// @param _x 
        /// @param _y 
        /// @param _w 
        /// @param _h 
        /// @param _type 
        /// @param _race 
        Structure(int _x, int _y, int _w, int _h, char _type, char _race): Entity(_type, _race), x(_x), y(_y), w(_w), h(_h)  {}
        int X() { return x;}
        int Y() { return y;}
        int W() { return w;}
        int H() { return h;}
        void paint() {
            for (int i=X();i<X()+W();i++) {
                for (int j=Y();j<Y()+H();j++) {
                    gotoXY(i,j);
                    
                    cout << colors[this->RACE()-'a']<<"" << TYPE()<<colors[4];
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
        hitBox getHitBox() {
            hitBox myHitBox;
            myHitBox.x = X();
            myHitBox.y = Y();
            myHitBox.w = W();
            myHitBox.h = H();
            return myHitBox;
        }
};