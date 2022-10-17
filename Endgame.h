#pragma once
#include "consts.h"
#include "Entities.h"

bool getWinner(vector<Worker*> &workers, vector<Soldier*> &soldiers)
{
    map<char,int> race_frecuency;
    for (auto worker : workers) race_frecuency[worker->RACE()]++;
    for (auto soldier : soldiers) race_frecuency[soldier->RACE()]++;
    for (auto frecuency : race_frecuency) if (frecuency.second == (workers.size()+soldiers.size())) return true;
    return false;
}