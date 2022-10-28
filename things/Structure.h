#pragma once
#include "Entity.h"
#include "../libs/hitBox.h"
#include "../libs/writer.h"
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
                     
    
            
                    attron(COLOR_PAIR(RACE()-'a'+1));
                    gotoXY(i,j);
                  
                   
                    printw("%c",TYPE());
                    refresh();
                    attroff(COLOR_PAIR(RACE()-'a'+1));
                 
                    refresh();
                    //cout << colors[4];
                    //cout << colors[this->RACE()-'a']<< TYPE()<<colors[4];
                }
            }
        }
        void erase() {
            for (int i=X();i<X()+W();i++) {
                for (int j=Y();j<Y()+H();j++) {
                    gotoXY(i,j);
                    printw(" ");
                    refresh();
                    //printfw(" %s",colors[4]);
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
        string getInfo() {
            string info = "";
            info.push_back(TYPE());
            info.push_back(' ');
            info.push_back(RACE());
            info.push_back(' ');
            info += to_string(X());
            info.push_back(' ');
            info += to_string(Y());
            info.push_back(' ');
            info += to_string(W());
            info.push_back(' ');
            info += to_string(H());
            return info;
        }
};