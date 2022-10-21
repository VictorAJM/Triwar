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
            _stats = colors[i-'a'];
            _stats.push_back(i);
            _stats = _stats+ "   G:"+to_string(gg)+" W: "+to_string(nW)+"  S: "+to_string(nS)+"  K: "+to_string(nK);
            stats = stats+_stats+ "       "+colors[4]; 
        }

        while (stats.size()<150) stats.push_back(' ');
        gotoXY(2,2);
        cout << stats <<"\n";
        gotoXY(130,2);
        string myTime = "Current Time: "+ to_string(timeCounter);
        cout << myTime << "\n"; 
    } catch(...) {
        gotoXY(2,2);
        cout << "Something went wrong";
    }

    return;
}