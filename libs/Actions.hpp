#pragma once
#include "../consts.h"
#include "../Entities.h"
#include "Area_Random.hpp"
void actionSkill(Skills_Structure* ST, entities &allEntities) {
    for (auto worker : allEntities.workers) if (worker->RACE() == ST->RACE()) {
        if (ST->SKILL()==0) {
            worker->setHealth(worker->HEALTH()+10);
        } else {
            worker->setDamage(worker->DAMAGE()+5);
        }
    }
    for (auto soldier : allEntities.soldiers) if (soldier->RACE() == ST->RACE()) {
        if (ST->SKILL()==0) {
            soldier->setHealth(soldier->HEALTH()+10);
        } else {
            soldier->setDamage(soldier->DAMAGE()+5);
        }
    }
    // add health to base and structures
}
void actionBase(Base* base, entities &allEntities)
{
    int choose = rand()%6;
    if (choose == 0 && base->GOLD()>=WORKER_COST) {
        // new worker
        vector<pair<int,int> > positions = AreaRandom::positionAround(base,allEntities);
        if (positions.size()>0) {
            int pos = rand()%(positions.size());
            Worker* newWorker = new Worker(positions[pos].first,positions[pos].second,base->RACE());
            newWorker->setHealth(newWorker->HEALTH()+base->getHealth());
            newWorker->setDamage(newWorker->HEALTH()+base->getDamage());
            newWorker->paint();
            allEntities.workers.push_back(newWorker);
            base->addGold(-WORKER_COST);
        }
    } else if (choose == 1 && base->GOLD()>=SOLDIER_COST) {
        // new Soldier
        vector<pair<int,int> > positions = AreaRandom::positionAround(base,allEntities);
        if (positions.size()>0) {
            int pos = rand()%(positions.size());
            Soldier* newSoldier = new Soldier(positions[pos].first,positions[pos].second,base->RACE());
            newSoldier->setHealth(newSoldier->HEALTH()+base->getHealth());
            newSoldier->setDamage(newSoldier->HEALTH()+base->getDamage());
            newSoldier->paint();
            allEntities.soldiers.push_back(newSoldier);
            base->addGold(-SOLDIER_COST);
        }
    } else if (choose == 2 && base->GOLD()>=WORKER_GENERATOR_COST) {
        int numberOfStructures = 0;
        for (auto sg : allEntities.soldier_generators) if (sg->RACE() == base->RACE()) numberOfStructures++;
        for (auto wg : allEntities.worker_generators) if (wg->RACE() == base->RACE()) numberOfStructures++;
        // agrega Worker_generator
        if (rand()%((numberOfStructures+2)/2) == 0) {
            pair<int,int> coords = AreaRandom::getPosition(7,7,allEntities);
            if (coords.first != 0) {
                allEntities.worker_generators.push_back(new Worker_Generator(coords.first+1,coords.second+1,base->RACE()));
                allEntities.worker_generators[allEntities.worker_generators.size()-1]->paint();
                base->addGold(-WORKER_GENERATOR_COST);
            }
        }
    } else if (choose == 3 && base->GOLD()>=SOLDIER_GENERATOR_COST) {
        // agrega Soldier_generator
        int numberOfStructures = 0;
        for (auto sg : allEntities.soldier_generators) if (sg->RACE() == base->RACE()) numberOfStructures++;
        for (auto wg : allEntities.worker_generators) if (wg->RACE() == base->RACE()) numberOfStructures++;
        // agrega Worker_generator
        if (rand()%((numberOfStructures+2)/2) == 0) {
            pair<int,int> coords = AreaRandom::getPosition(7,7,allEntities);
            if (coords.first != 0) {
                allEntities.soldier_generators.push_back(new Soldier_Generator(coords.first+1,coords.second+1,base->RACE()));
                allEntities.soldier_generators[allEntities.soldier_generators.size()-1]->paint();
                base->addGold(-SOLDIER_GENERATOR_COST);
            }
        }
    } else if (choose == 4 && base->GOLD()>=SKILLS_STRUCTURE_COST) {
        int numberOfStructures = 0;
        for (auto sg : allEntities.soldier_generators) if (sg->RACE() == base->RACE()) numberOfStructures++;
        for (auto wg : allEntities.worker_generators) if (wg->RACE() == base->RACE()) numberOfStructures++;
        numberOfStructures/=2;
        for (auto st : allEntities.skills_structures) if (st->RACE() == base->RACE()) numberOfStructures++;
        if (rand()%(numberOfStructures+2)/2 == 0) {
            pair<int,int> coords = AreaRandom::getPosition(4,4,allEntities);
            if (coords.first != 0) {
                allEntities.skills_structures.push_back(new Skills_Structure(coords.first+1, coords.second+1, base->RACE()));
                allEntities.skills_structures[allEntities.skills_structures.size()-1]->paint();
                base->addGold(-SKILLS_STRUCTURE_COST);
            }
        }
    } else if (choose == 5 && base->GOLD()>=KAMIKAZE_COST) {
        int numberOfStructures = 0;
        for (auto sg : allEntities.soldier_generators) if (sg->RACE() != base->RACE()) numberOfStructures++;
        for (auto wg : allEntities.worker_generators) if (wg->RACE() != base->RACE()) numberOfStructures++;
        for (auto st : allEntities.skills_structures) if (st->RACE() != base->RACE()) numberOfStructures++;
        vector<pair<int,int> > positions = AreaRandom::positionAround(base,allEntities);
        if (positions.size()==0) return;
        pair<int,int> coords = positions[rand()%(positions.size())];
        if (coords.first != 0) {
            allEntities.kamikazes.push_back(new Kamikaze(coords.first,coords.second, base->RACE()));
            allEntities.kamikazes[allEntities.kamikazes.size()-1]->paint();
            base->addGold(-KAMIKAZE_COST);
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
