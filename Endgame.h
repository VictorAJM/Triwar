#pragma once
#include "consts.h"
#include "writer.h"
#include "Entities.h"

bool getWinner(vector<Worker*> &workers, vector<Soldier*> &soldiers, vector<Base*> &bases)
{
    for (auto base : bases) if (base->GOLD()>30000) return true;
    try {
    map<char,int> race_frecuency;
    for (auto worker : workers) race_frecuency[worker->RACE()]++;
    for (auto soldier : soldiers) race_frecuency[soldier->RACE()]++;
    for (auto frecuency : race_frecuency) if (frecuency.second == int(workers.size()+soldiers.size())) {
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