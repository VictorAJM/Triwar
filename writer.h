#pragma once
#include "consts.h"
void gotoXY(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}
void ocultarCursor()
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 2;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}
void limpiar_pantalla()
{
    for (int i=0;i<40;i++) {
        for (int j=0;j<150;j++) {
            gotoXY(j,i);
            printf(" ");
        }
    }
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
    for (int i=2;i<148;i++) {
        gotoXY(i,3); printf("%c",205); charMap[i][3] = 205;
        gotoXY(i,39); printf("%c",205);charMap[i][39] = 205;
    }
    for (int i=4;i<39;i++) {
        gotoXY(2,i); printf("%c",186); charMap[2][i] = 186;
        gotoXY(147,i); printf("%c",186); charMap[147][i] = 186;
    }
    gotoXY(2,3); charMap[2][3] = 201; printf("%c",201);
    gotoXY(2,39); printf("%c",200); charMap[2][39] = 200;
    gotoXY(147,3); printf("%c",187); charMap[147][3] = 187;
    gotoXY(147,39); printf("%c",188); charMap[147][39] = 188;
}