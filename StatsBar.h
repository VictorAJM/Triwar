#pragma once
#include "consts.h"
#include "Entities.h"

void drawStats(entities &allEntities)
{
    try {
         string stats;
        for (int i='a';i<='c';i++) {
            string _stats;
            int nW,nS,nK,gg;
            nW = nS = nK = gg = 0;
            for (auto worker: allEntities.workers) if (worker->RACE() == i) nW++;
            for (auto soldier : allEntities.soldiers) if (soldier->RACE() == i) nS++;
            for (auto kamikaze : allEntities.kamikazes) if (kamikaze->RACE() == i) nK++;
            for (auto base : allEntities.bases) if (base->RACE() == i) gg = base->GOLD();
            /*_stats = colors[i-'a'];
            _stats.push_back(i);
            _stats = _stats+ "   G:"+to_string(gg)+" W: "+to_string(nW)+"  S: "+to_string(nS)+"  K: "+to_string(nK);
            stats = stats+_stats+ "       "+colors[4]; */
            _stats.push_back(i);
            _stats = _stats+ "   G:"+to_string(gg)+" W: "+to_string(nW)+"  S: "+to_string(nS)+"  K: "+to_string(nK);
            stats = stats+_stats+ "       ";
        }

        while (stats.size()<150) stats.push_back(' ');
        gotoXY(2,2);
        int p = 2;
        for (char i : stats) {
            gotoXY(p,2);
            printw("%c",i);
            refresh();
            p++;
        }
        
        
        gotoXY(130,2);
        string myTime = "Current Time: "+ to_string(timeCounter);
        p = 130;
        for (char i : myTime) {
            gotoXY(p,2);
            printw("%c",i);
            refresh();
            p++;
        }
    } catch(...) {
        gotoXY(2,2);
        printw("Something went wrong");
         refresh();
    }

    return;
}