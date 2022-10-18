#pragma once
#include "consts.h"
#include "Entities.h"
void actionBase(Base* base, entities &allEntities)
{
    int doORdont = rand()%2;
    if (!doORdont) return;
    int choose = rand()%4;
    if (choose == 0 && base->GOLD()>=50) {
        // new worker
        vector<pair<int,int> > positions;
        for (int i=base->X()-1;i<=base->X()+base->W();i++) for (int j=base->Y()-1;j<=base->Y()+base->H();j++) {
            bool free = true;
            for (auto _base : allEntities.bases) {
                if (hitBox(i,j,1,1).collisionWith(_base->getHitBox())) free = false;
            } 
            for (auto worker : allEntities.workers) {
                if (hitBox(i,j,1,1).collisionWith(worker->getHitBox())) free = false;
            } 
            for (auto soldier : allEntities.soldiers) {
                if (hitBox(i,j,1,1).collisionWith(soldier->getHitBox())) free = false;
            } 
            for (auto mineral : allEntities.minerals) {
                if (hitBox(i,j,1,1).collisionWith(mineral->getHitBox())) free = false;
            } 
            if (free) positions.push_back({i,j});
        }
        if (positions.size()>0) {
        int pos = rand()%(positions.size());
        Worker* newWorker = new Worker(positions[pos].first,positions[pos].second,base->RACE());
        newWorker->paint();
        allEntities.workers.push_back(newWorker);
        base->addGold(-50);
        }
    } else if (choose == 1 && base->GOLD()>=50) {
        // new Soldier
        vector<pair<int,int> > positions;
        for (int i=base->X()-1;i<=base->X()+base->W();i++) for (int j=base->Y()-1;j<=base->Y()+base->H();j++) {
            bool free = true;
            for (auto _base : allEntities.bases) {
                if (hitBox(i,j,1,1).collisionWith(_base->getHitBox())) free = false;
            } 
            for (auto worker : allEntities.workers) {
                if (hitBox(i,j,1,1).collisionWith(worker->getHitBox())) free = false;
            } 
            for (auto soldier : allEntities.soldiers) {
                if (hitBox(i,j,1,1).collisionWith(soldier->getHitBox())) free = false;
            } 
            for (auto mineral : allEntities.minerals) {
                if (hitBox(i,j,1,1).collisionWith(mineral->getHitBox())) free = false;
            } 
            if (free) positions.push_back({i,j});
        }
        if (positions.size()>0) {
        int pos = rand()%(positions.size());
        Soldier* newSoldier = new Soldier(positions[pos].first,positions[pos].second,base->RACE());
        newSoldier->paint();
        allEntities.soldiers.push_back(newSoldier);
        base->addGold(-50);
        }
    } else if (choose == 2 && base->GOLD()>=200) {
        
        // agrega Worker_generator
    } else if (choose == 3 && base->GOLD()>=200) {
        // genera Area de 5x5
        // agrega Soldier_generator
    }   
}
void actionBase(Base* base, vector<Base*> &bases, vector<Worker*> &workers, vector<Soldier*> &soldiers, vector<Mineral*> &minerals)
{
    int doORdont = rand()%2;
    if (!doORdont) return;
    int choose = rand()%4;
    if (choose == 0 && base->GOLD()>=50) {
        // new worker
        vector<pair<int,int> > positions;
        for (int i=base->X()-1;i<=base->X()+base->W();i++) for (int j=base->Y()-1;j<=base->Y()+base->H();j++) {
            bool free = true;
            for (auto _base : bases) {
                if (hitBox(i,j,1,1).collisionWith(_base->getHitBox())) free = false;
            } 
            for (auto worker : workers) {
                if (hitBox(i,j,1,1).collisionWith(worker->getHitBox())) free = false;
            } 
            for (auto soldier : soldiers) {
                if (hitBox(i,j,1,1).collisionWith(soldier->getHitBox())) free = false;
            } 
            for (auto mineral : minerals) {
                if (hitBox(i,j,1,1).collisionWith(mineral->getHitBox())) free = false;
            } 
            if (free) positions.push_back({i,j});
        }
        if (positions.size()>0) {
        int pos = rand()%(positions.size());
        Worker* newWorker = new Worker(positions[pos].first,positions[pos].second,base->RACE());
        newWorker->paint();
        workers.push_back(newWorker);
        base->addGold(-50);
        }
    } else if (choose == 1 && base->GOLD()>=50) {
        // new Soldier
        vector<pair<int,int> > positions;
        for (int i=base->X()-1;i<=base->X()+base->W();i++) for (int j=base->Y()-1;j<=base->Y()+base->H();j++) {
            bool free = true;
            for (auto _base : bases) {
                if (hitBox(i,j,1,1).collisionWith(_base->getHitBox())) free = false;
            } 
            for (auto worker : workers) {
                if (hitBox(i,j,1,1).collisionWith(worker->getHitBox())) free = false;
            } 
            for (auto soldier : soldiers) {
                if (hitBox(i,j,1,1).collisionWith(soldier->getHitBox())) free = false;
            } 
            for (auto mineral : minerals) {
                if (hitBox(i,j,1,1).collisionWith(mineral->getHitBox())) free = false;
            } 
            if (free) positions.push_back({i,j});
        }
        if (positions.size()>0) {
        int pos = rand()%(positions.size());
        Soldier* newSoldier = new Soldier(positions[pos].first,positions[pos].second,base->RACE());
        newSoldier->paint();
        soldiers.push_back(newSoldier);
        base->addGold(-50);
        }
    } else if (choose == 2 && base->GOLD()>=200) {
        
        // agrega Worker_generator
    } else if (choose == 3 && base->GOLD()>=200) {
        // genera Area de 5x5
        // agrega Soldier_generator
    }
}