#pragma once
#include "../consts.h"
#include "../Entities.h"
#include "hitBox.h"
namespace AreaRandom {
    bool freePosition(hitBox _hitbox, entities &allEntities)
    {
        bool free = true;
        for (auto base : allEntities.bases) if (_hitbox.collisionWith(base->getHitBox())) free = false;
        for (auto worker : allEntities.workers) if (_hitbox.collisionWith(worker->getHitBox())) free = false;
        for (auto soldier : allEntities.soldiers) if (_hitbox.collisionWith(soldier->getHitBox())) free = false;
        for (auto mineral : allEntities.minerals) if (_hitbox.collisionWith(mineral->getHitBox())) free = false;
        for (auto kamikaze : allEntities.kamikazes) if (_hitbox.collisionWith(kamikaze->getHitBox())) free = false;
        for (auto worker_generator : allEntities.worker_generators) if (_hitbox.collisionWith(worker_generator->getHitBox())) free = false;
        for (auto soldier_generator : allEntities.soldier_generators) if (_hitbox.collisionWith(soldier_generator->getHitBox())) free = false;
        for (auto skill_generator : allEntities.skills_structures) if (_hitbox.collisionWith(skill_generator->getHitBox())) free = false;
        return free;
    }
    pair<int,int> getPosition(int x, int y, entities &allEntities) 
    {
        vector<pair<int,int> > possible_positions;
        for (int i=LEFT_MAP+2;i<RIGHT_MAP-x-1;i++) {
            for (int j=TOP_MAP+2;j<BOT_MAP-y-1;j++) {
                if (freePosition(hitBox(i-1,j-1,x+2,y+2), allEntities)) possible_positions.push_back(make_pair(i,j));
            }
        }
        if (possible_positions.size()==0) return make_pair(0,0);
        return possible_positions[rand()%(possible_positions.size())];
    }
    vector<pair<int,int> > positionAround(Base* base, entities &allEntities) 
    {
        vector<pair<int,int> > positions;
        for (int i=base->X()-1;i<=base->X()+base->W();i++) {
            for (int j=base->Y()-1;j<=base->Y()+base->H();j++) {
                if (freePosition(hitBox(i,j,1,1), allEntities)) positions.push_back(make_pair(i,j));
            }
        }
        return positions;
    }
    vector<pair<int,int> > positionAround(Worker_Generator* wg, entities &allEntities) 
    {
        vector<pair<int,int> > positions;
        for (int i=wg->X()-1;i<=wg->X()+wg->W();i++) {
            for (int j=wg->Y()-1;j<=wg->Y()+wg->H();j++) {
                if (freePosition(hitBox(i,j,1,1), allEntities)) positions.push_back(make_pair(i,j));
            }
        }
        return positions;
    }
    vector<pair<int,int> > positionAround(Soldier_Generator* sg, entities &allEntities) 
    {
        vector<pair<int,int> > positions;
        for (int i=sg->X()-1;i<=sg->X()+sg->W();i++) {
            for (int j=sg->Y()-1;j<=sg->Y()+sg->H();j++) {
                if (freePosition(hitBox(i,j,1,1), allEntities)) positions.push_back(make_pair(i,j));
            }
        }
        return positions;
    }
}