#pragma once
#include "consts.h"
#include "Entities.h"

void drawStats(entities &allEntities)
{
    try {
         string stats;
        for (int i=0;i<(int)allEntities.bases.size();i++) {
            string _stats;
            int numOfW,numOfS;
            numOfW = numOfS = 0;
            for (auto worker :allEntities. workers) if (worker->RACE() == allEntities.bases[i]->RACE()) numOfW++;
            for (auto soldier : allEntities.soldiers) if (soldier->RACE() == allEntities.bases[i]->RACE()) numOfS++;
            _stats = "Base: ";
            _stats.push_back(allEntities.bases[i]->RACE());
            _stats = _stats+"   G: "+to_string(allEntities.bases[i]->GOLD())+" W: "+ to_string(numOfW) + " S: "+to_string(numOfS);
            stats = stats+_stats+ "             " ;
        }
        while (stats.size()<150) stats.push_back(' ');
        gotoXY(2,2);
        cout << stats <<"\n";
    } catch(...) {
        gotoXY(2,2);
        cout << "Something went wrong";
    }

    return;
}