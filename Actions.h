#pragma once
#include "consts.h"
#include "Entities.h"
#include "Area_Random.hpp"
void actionBase(Base* base, entities &allEntities)
{
    int doORdont = rand()%2;
    if (!doORdont) return;
    int choose = rand()%4;
    if (choose == 0 && base->GOLD()>=50) {
        // new worker
        vector<pair<int,int> > positions = AreaRandom::positionAround(base,allEntities);
        if (positions.size()>0) {
            int pos = rand()%(positions.size());
            Worker* newWorker = new Worker(positions[pos].first,positions[pos].second,base->RACE());
            newWorker->paint();
            allEntities.workers.push_back(newWorker);
            base->addGold(-50);
        }
    } else if (choose == 1 && base->GOLD()>=50) {
        // new Soldier
        vector<pair<int,int> > positions = AreaRandom::positionAround(base,allEntities);
        if (positions.size()>0) {
            int pos = rand()%(positions.size());
            Soldier* newSoldier = new Soldier(positions[pos].first,positions[pos].second,base->RACE());
            newSoldier->paint();
            allEntities.soldiers.push_back(newSoldier);
            base->addGold(-50);
        }
    } else if (choose == 2 && base->GOLD()>=200) {
        int numberOfStructures = 0;
        for (auto sg : allEntities.soldier_generators) if (sg->RACE() == base->RACE()) numberOfStructures++;
        for (auto wg : allEntities.worker_generators) if (wg->RACE() == base->RACE()) numberOfStructures++;
        // agrega Worker_generator
        if (rand()%((numberOfStructures+2)/2) == 0) {
            pair<int,int> coords = AreaRandom::getPosition(5,5,allEntities);
            allEntities.worker_generators.push_back(new Worker_Generator(coords.first,coords.second,base->RACE()));
            allEntities.worker_generators[allEntities.worker_generators.size()-1]->paint();
            base->addGold(-200);
        }
    } else if (choose == 3 && base->GOLD()>=200) {
        // agrega Soldier_generator
        int numberOfStructures = 0;
        for (auto sg : allEntities.soldier_generators) if (sg->RACE() == base->RACE()) numberOfStructures++;
        for (auto wg : allEntities.worker_generators) if (wg->RACE() == base->RACE()) numberOfStructures++;
        // agrega Worker_generator
        if (rand()%((numberOfStructures+2)/2) == 0) {
            pair<int,int> coords = AreaRandom::getPosition(5,5,allEntities);
            allEntities.soldier_generators.push_back(new Soldier_Generator(coords.first,coords.second,base->RACE()));
            allEntities.soldier_generators[allEntities.soldier_generators.size()-1]->paint();
            base->addGold(-200);
        }
    }  
    if (base->GOLD()>=1000) {
        int again = rand()%2;
        if (again) {
            base->addGold(-100);
            actionBase(base, allEntities);
        }
    } 
}
