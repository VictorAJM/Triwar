#pragma once
#include "../libs/writer.h"
#include "../consts.h"
void gotoXY(int x, int y)
{
    move(y,x);
}
void ocultarCursor()
{
    printf("\e[?25l");
}
void limpiar_pantalla()
{
    system("clear");
}
void crearCharMatrix()
{
    string aux;
    for (int i=0;i<40;i++) aux.push_back(' ');
    for (int i=0;i<150;i++) charMap.push_back(aux);
}
void pintar_limites()
{

    limpiar_pantalla();
    attron(COLOR_PAIR(5));
    for (int i=2;i<148;i++) {
        try {
        gotoXY(i,3); printw("#");charMap[i][3] = (char)205;
        gotoXY(i,39); printw("#");charMap[i][39] = (char)205;
        } catch(...) {
            return;
        }
    }
    for (int i=4;i<39;i++) {
        try {
            gotoXY(2,i); printw("#"); charMap[2][i] = (char)186;
            gotoXY(147,i); printw("#");charMap[147][i] = (char)186;
        } catch(...) {
            return ;
        }
    }
     attroff(COLOR_PAIR(5));
}