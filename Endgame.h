#pragma once
#include "consts.h"
#include "writer.h"
#include "Entities.h"
bool getWinner(entities &allEntities)
{
    for (auto base : allEntities.bases) if (base->GOLD()>30000) return true;
    try {
    map<char,int> race_frecuency;
    for (auto base : allEntities.bases) race_frecuency[base->RACE()]=0;
    for (auto worker : allEntities.workers) race_frecuency[worker->RACE()]++;
    for (auto soldier : allEntities.soldiers) race_frecuency[soldier->RACE()]++;
    for (auto frecuency : race_frecuency) if (frecuency.second == 0) {
        for (int i=0;i<allEntities.bases.size();i++) if (frecuency.first==allEntities.bases[i]->RACE()) {
            allEntities.bases[i]->erase();
            allEntities.bases.erase(allEntities.bases.begin()+i);
            i=0;
        }
    }
    for (auto frecuency : race_frecuency) if (frecuency.second == int(allEntities.workers.size()+allEntities.soldiers.size())) {
        gotoXY(1,1);
        cout << "Winner\n";
        return true;
    }
    return false;
    } catch (...) {
        cout << "WTF\n";
        return false;
    } 
}