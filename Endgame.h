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
            for (int i=0;i<(int)allEntities.bases.size();i++) if (frecuency.first==allEntities.bases[i]->RACE()) {
                allEntities.bases[i]->erase();
                allEntities.bases.erase(allEntities.bases.begin()+i);
                i=0;
            }
            for (int i=0;i<(int)allEntities.worker_generators.size();i++) if (frecuency.first==allEntities.worker_generators[i]->RACE()) {
                allEntities.worker_generators[i]->erase();
                allEntities.worker_generators.erase(allEntities.worker_generators.begin()+i);
                i=0;
            }
            for (int i=0;i<(int)allEntities.soldier_generators.size();i++) if (frecuency.first==allEntities.soldier_generators[i]->RACE()) {
                allEntities.soldier_generators[i]->erase();
                allEntities.soldier_generators.erase(allEntities.soldier_generators.begin()+i);
                i=0;
            }
            for (int i=0;i<(int)allEntities.skills_structures.size();i++) if (frecuency.first==allEntities.skills_structures[i]->RACE()) {
                allEntities.skills_structures[i]->erase();
                allEntities.skills_structures.erase(allEntities.skills_structures.begin()+i);
                i=0;
            }
            for (int i=0;i<(int)allEntities.kamikazes.size();i++) if (frecuency.first==allEntities.kamikazes[i]->RACE()) {
                allEntities.kamikazes[i]->erase();
                allEntities.kamikazes.erase(allEntities.kamikazes.begin()+i);
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