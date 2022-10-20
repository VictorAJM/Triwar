#pragma once
#include "consts.h"
#include "Entities.h"
#include "Area_Random.hpp"
void moveKamikaze(Kamikaze* kamikaze, entities &allEntities)
{
    kamikaze->erase();
    bool visited[150][40];
    int distance[150][40];
        for (int i=0;i<150;i++) {
            for (int j=0;j<40;j++) distance[i][j] = inf;
        }
        for (int i=LEFT_MAP;i<=RIGHT_MAP;i++) {
            for (int j=TOP_MAP;j<=BOT_MAP;j++) visited[i][j] = false;
        }
        queue<pair<pair<int,int> ,int> > dist_to_generator;
        for (auto _mineral : allEntities.minerals) {
            int w = _mineral->W();
            int h = _mineral->H();
            for (int i=_mineral->X();i<_mineral->X()+w;i++) {
                for (int j=_mineral->Y();j<_mineral->Y()+h;j++) {
                    
                    visited[i][j]=true;
                }
            }
        }
        for (auto _base : allEntities.bases) {
            int w = _base->W();
            int h = _base->H();
            for (int i=_base->X();i<_base->X()+w;i++) {
                for (int j=_base->Y();j<_base->Y()+h;j++) {
                    visited[i][j]=true;
                }
            }
        }
        for (auto wg : allEntities.worker_generators) {
            int w = wg->W();
            int h = wg->H();
            for (int i=wg->X();i<wg->X()+w;i++) {
                for (int j=wg->Y();j<wg->Y()+h;j++) {
                    if (wg->RACE() != kamikaze->RACE()) dist_to_generator.push({{i,j},0});
                    visited[i][j]=true;
                }
            }
        }
        for (auto sg : allEntities.soldier_generators) {
            int w = sg->W();
            int h = sg->H();
            for (int i=sg->X();i<sg->X()+w;i++) {
                for (int j=sg->Y();j<sg->Y()+h;j++) {
                    if (sg->RACE() != kamikaze->RACE()) dist_to_generator.push({{i,j},0});
                    visited[i][j]=true;
                }
            }
        }
        for (auto st : allEntities.skills_structures) {
            int w = st->W();
            int h = st->H();
            for (int i=st->X();i<st->X()+w;i++) {
                for (int j=st->Y();j<st->Y()+h;j++) {
                    if (st->RACE() != kamikaze->RACE()) dist_to_generator.push({{i,j},0});
                    visited[i][j]=true;
                }
            }
        }
        for (auto _kamikaze : allEntities.kamikazes) {
            int w = 1;
            int h = 1;
            for (int i=_kamikaze->X();i<_kamikaze->X()+w;i++) {
                for (int j=_kamikaze->Y();j<_kamikaze->Y()+h;j++) {
                    if (_kamikaze->ID() != kamikaze->ID())
                    visited[i][j]=true;
                }
            }
        }
        for (auto _worker : allEntities.workers) {
            visited[_worker->X()][_worker->Y()] = true;
        }
        for (auto _soldier : allEntities.soldiers) {
            visited[_soldier->X()][_soldier->Y()] = true;
        }
        while (!dist_to_generator.empty()) {
            auto dist = dist_to_generator.front();
            distance[dist.first.first][dist.first.second] = dist.second;
            dist_to_generator.pop();
            if (dist.first.first>LEFT_MAP && !visited[dist.first.first-1][dist.first.second]) {
                visited[dist.first.first-1][dist.first.second] = true;
                dist_to_generator.push({{dist.first.first-1,dist.first.second},dist.second+1});
            } 
            if (dist.first.first<RIGHT_MAP && !visited[dist.first.first+1][dist.first.second]) {
                visited[dist.first.first+1][dist.first.second] = true;
                dist_to_generator.push({{dist.first.first+1,dist.first.second},dist.second+1});
            } 
            if (dist.first.second>TOP_MAP && !visited[dist.first.first][dist.first.second-1]) {
                visited[dist.first.first][dist.first.second-1] = true;
                dist_to_generator.push({{dist.first.first,dist.first.second-1},dist.second+1});
            } 
            if (dist.first.second<BOT_MAP && !visited[dist.first.first][dist.first.second+1]) {
                visited[dist.first.first][dist.first.second+1] = true;
                dist_to_generator.push({{dist.first.first,dist.first.second+1},dist.second+1});
            } 
        }
        int myDistance = distance[kamikaze->X()][kamikaze->Y()];
        if (myDistance == 1) {
   
            bool used = false;
            for (int i=0;i<allEntities.soldier_generators.size();i++) {
                auto sg = allEntities.soldier_generators[i];
                if (sg->RACE() != kamikaze->RACE() && sg->getHitBox().shareSide(kamikaze->getHitBox())) {
                    sg->erase();
                    allEntities.soldier_generators.erase(allEntities.soldier_generators.begin()+i);
                    i=0;
                    used = true;
                } 
            }
            for (int i=0;i<allEntities.worker_generators.size();i++) {
                auto wg = allEntities.worker_generators[i];
                if (wg->RACE() != kamikaze->RACE() && wg->getHitBox().shareSide(kamikaze->getHitBox())) {
                    wg->erase();
                    allEntities.worker_generators.erase(allEntities.worker_generators.begin()+i);
                    i=0;
                    used = true;
                } 
            }
            for (int i=0;i<allEntities.skills_structures.size();i++) {
                auto ss = allEntities.skills_structures[i];
                if (ss->RACE() != kamikaze->RACE() && ss->getHitBox().shareSide(kamikaze->getHitBox())) {
                    ss->erase();
                    allEntities.skills_structures.erase(allEntities.skills_structures.begin()+i);
                    i=0;
                    used = true;
                } 
            }

            if (used) {
                int id = kamikaze->ID();
                for (int i=0;i<allEntities.kamikazes.size();i++) {
                    if (allEntities.kamikazes[i]->ID() == id) {
                        kamikaze->erase();
                        allEntities.kamikazes.erase(allEntities.kamikazes.begin()+i);
                        i=0;
                    }
                }
                return;
            }
            // if true erase Kamikaze
            kamikaze->paint();
            return;
            // else paint return
        }
        bool moved = false;
        if (kamikaze->X()>LEFT_MAP && distance[kamikaze->X()-1][kamikaze->Y()] < myDistance) {
            myDistance = distance[kamikaze->X()-1][kamikaze->Y()];
            moved = true;
        } 
        if (kamikaze->X()<RIGHT_MAP && distance[kamikaze->X()+1][kamikaze->Y()] < myDistance) {
            myDistance = distance[kamikaze->X()+1][kamikaze->Y()];
            moved = true;
        } 
        if (kamikaze->Y()>TOP_MAP && distance[kamikaze->X()][kamikaze->Y()-1] < myDistance) {
            myDistance = distance[kamikaze->X()][kamikaze->Y()-1];
            moved = true;
        } 
        if (kamikaze->Y()<BOT_MAP && distance[kamikaze->X()][kamikaze->Y()+1] < myDistance) {
            myDistance = distance[kamikaze->X()][kamikaze->Y()+1];
            moved = true;
        } 
        if (!moved) {
            kamikaze->paint();
            return;
        }
        if (kamikaze->X()>LEFT_MAP && distance[kamikaze->X()-1][kamikaze->Y()] == myDistance) {
            kamikaze->setX(kamikaze->X()-1);
        } else if (kamikaze->X()<RIGHT_MAP && distance[kamikaze->X()+1][kamikaze->Y()] == myDistance) {
            kamikaze->setX(kamikaze->X()+1);
        } else if (kamikaze->Y()>TOP_MAP && distance[kamikaze->X()][kamikaze->Y()-1] == myDistance) {
            kamikaze->setY(kamikaze->Y()-1);
        } else if (kamikaze->Y()<BOT_MAP && distance[kamikaze->X()][kamikaze->Y()+1] == myDistance) {
            kamikaze->setY(kamikaze->Y()+1);
        } else {

        }
            bool used = false;
            for (int i=0;i<allEntities.soldier_generators.size();i++) {
                auto &sg = allEntities.soldier_generators[i];
                if (sg->RACE() != kamikaze->RACE() && sg->getHitBox().shareSide(kamikaze->getHitBox())) {
                    sg->erase();
                    allEntities.soldier_generators.erase(allEntities.soldier_generators.begin()+i);
                    i=0;
                    used = true;
                } 
            }
            for (int i=0;i<allEntities.worker_generators.size();i++) {
                auto &wg = allEntities.worker_generators[i];
                if (wg->RACE() != kamikaze->RACE() && wg->getHitBox().shareSide(kamikaze->getHitBox())) {
                    wg->erase();
                    allEntities.worker_generators.erase(allEntities.worker_generators.begin()+i);
                    i=0;
                    used = true;
                } 
            }
            for (int i=0;i<allEntities.skills_structures.size();i++) {
                auto &ss = allEntities.skills_structures[i];
                if (ss->RACE() != kamikaze->RACE() && ss->getHitBox().shareSide(kamikaze->getHitBox())) {
                    ss->erase();
                    allEntities.skills_structures.erase(allEntities.skills_structures.begin()+i);
                    i=0;
                    used = true;
                } 
            }

            if (used) {
                int id = kamikaze->ID();
                for (int i=0;i<allEntities.kamikazes.size();i++) {
                    if (allEntities.kamikazes[i]->ID() == id) {
                        kamikaze->erase();
                        allEntities.kamikazes.erase(allEntities.kamikazes.begin()+i);
                        i=0;
                    }
                }
                return;
            }
            // if true erase Kamikaze
            kamikaze->paint();
            return;
}
void moveWorker(Worker* worker, entities &allEntities)
{
    worker->erase();
    if (worker->GOLD() == 0) {
        bool visited[150][40];
        int distance[150][40];
        for (int i=0;i<150;i++) {
            for (int j=0;j<40;j++) distance[i][j] = inf;
        }
        for (int i=LEFT_MAP;i<=RIGHT_MAP;i++) {
            for (int j=TOP_MAP;j<=BOT_MAP;j++) visited[i][j] = false;
        }
        queue<pair<pair<int,int> ,int> > dist_to_mineral;
        for (auto _mineral : allEntities.minerals) {
            int w = _mineral->W();
            int h = _mineral->H();
            for (int i=_mineral->X();i<_mineral->X()+w;i++) {
                for (int j=_mineral->Y();j<_mineral->Y()+h;j++) {
                    dist_to_mineral.push({{i,j},0});
                    visited[i][j]=true;
                }
            }
        }
        for (auto _base : allEntities.bases) {
            int w = _base->W();
            int h = _base->H();
            for (int i=_base->X();i<_base->X()+w;i++) {
                for (int j=_base->Y();j<_base->Y()+h;j++) {
                    visited[i][j]=true;
                }
            }
        }
        for (auto wg : allEntities.worker_generators) {
            int w = wg->W();
            int h = wg->H();
            for (int i=wg->X();i<wg->X()+w;i++) {
                for (int j=wg->Y();j<wg->Y()+h;j++) {
                    visited[i][j]=true;
                }
            }
        }
        for (auto sg : allEntities.soldier_generators) {
            int w = sg->W();
            int h = sg->H();
            for (int i=sg->X();i<sg->X()+w;i++) {
                for (int j=sg->Y();j<sg->Y()+h;j++) {
                    visited[i][j]=true;
                }
            }
        }
        for (auto st : allEntities.skills_structures) {
            int w = st->W();
            int h = st->H();
            for (int i=st->X();i<st->X()+w;i++) {
                for (int j=st->Y();j<st->Y()+h;j++) {
                    visited[i][j]=true;
                }
            }
        }
        for (auto kamikaze : allEntities.kamikazes) {
            int w = 1;
            int h = 1;
            for (int i=kamikaze->X();i<kamikaze->X()+w;i++) {
                for (int j=kamikaze->Y();j<kamikaze->Y()+h;j++) {
                    visited[i][j]=true;
                }
            }
        }
        for (auto _worker : allEntities.workers) {
            if (worker->ID() != _worker->ID()) visited[_worker->X()][_worker->Y()] = true;
        }
        for (auto _soldier : allEntities.soldiers) {
            visited[_soldier->X()][_soldier->Y()] = true;
        }
        while (!dist_to_mineral.empty()) {
            auto dist = dist_to_mineral.front();
            distance[dist.first.first][dist.first.second] = dist.second;
            dist_to_mineral.pop();
            if (dist.first.first>LEFT_MAP && !visited[dist.first.first-1][dist.first.second]) {
                visited[dist.first.first-1][dist.first.second] = true;
                dist_to_mineral.push({{dist.first.first-1,dist.first.second},dist.second+1});
            } 
            if (dist.first.first<RIGHT_MAP && !visited[dist.first.first+1][dist.first.second]) {
                visited[dist.first.first+1][dist.first.second] = true;
                dist_to_mineral.push({{dist.first.first+1,dist.first.second},dist.second+1});
            } 
            if (dist.first.second>TOP_MAP && !visited[dist.first.first][dist.first.second-1]) {
                visited[dist.first.first][dist.first.second-1] = true;
                dist_to_mineral.push({{dist.first.first,dist.first.second-1},dist.second+1});
            } 
            if (dist.first.second<BOT_MAP && !visited[dist.first.first][dist.first.second+1]) {
                visited[dist.first.first][dist.first.second+1] = true;
                dist_to_mineral.push({{dist.first.first,dist.first.second+1},dist.second+1});
            } 
        }
        
        int myDistance = distance[worker->X()][worker->Y()];
        if (myDistance <= 1) {
            worker->paint();
            int id = -1;
            for (auto mineral : allEntities.minerals) if (worker->getHitBox().shareSide(mineral->getHitBox())) {
                worker->setGold(30);
                mineral->setUses(mineral->getUses()-1);
                if (mineral->getUses()==0) id = mineral->ID();
            }
            if (id!=-1) {
                for (int i=0;i<allEntities.minerals.size();i++) if (allEntities.minerals[i]->ID() == id) {
                    allEntities.minerals[i]->erase();
                    allEntities.minerals.erase(allEntities.minerals.begin()+i);
                    i=0;
                }
                pair<int,int> coords = AreaRandom::getPosition(3,3, allEntities);
                if (coords.first != 0) {
                    Mineral* mineral = new Mineral(coords.first,coords.second);
                    mineral->paint();
                    allEntities.minerals.push_back(mineral);
                }
            }
            return;
        } 
        bool moved = false;
        if (worker->X()>LEFT_MAP && distance[worker->X()-1][worker->Y()] < myDistance) {
            myDistance = distance[worker->X()-1][worker->Y()];
            moved = true;
        } 
        if (worker->X()<RIGHT_MAP && distance[worker->X()+1][worker->Y()] < myDistance) {
            myDistance = distance[worker->X()+1][worker->Y()];
            moved = true;
        } 
        if (worker->Y()>TOP_MAP && distance[worker->X()][worker->Y()-1] < myDistance) {
            myDistance = distance[worker->X()][worker->Y()-1];
            moved = true;
        } 
        if (worker->Y()<BOT_MAP && distance[worker->X()][worker->Y()+1] < myDistance) {
            myDistance = distance[worker->X()][worker->Y()+1];
            moved = true;
        } 
        if (!moved) {
            worker->paint();
            return;
        }
        if (worker->X()>LEFT_MAP && distance[worker->X()-1][worker->Y()] == myDistance) {
            worker->setX(worker->X()-1);
        } else if (worker->X()<RIGHT_MAP && distance[worker->X()+1][worker->Y()] == myDistance) {
            worker->setX(worker->X()+1);
        } else if (worker->Y()>TOP_MAP && distance[worker->X()][worker->Y()-1] == myDistance) {
            worker->setY(worker->Y()-1);
        } else if (worker->Y()<BOT_MAP && distance[worker->X()][worker->Y()+1] == myDistance) {
            worker->setY(worker->Y()+1);
        } else {

        }
        worker->paint();
    } else {
        bool visited[150][40];
        int distance[150][40];
        for (int i=0;i<150;i++) {
            for (int j=0;j<40;j++) distance[i][j] = inf;
        }
        for (int i=LEFT_MAP;i<=RIGHT_MAP;i++) {
            for (int j=TOP_MAP;j<=BOT_MAP;j++) visited[i][j] = false;
        }
        
        queue<pair<pair<int,int> ,int> > dist_to_base;
        for (auto _mineral : allEntities.minerals) {
            int w = _mineral->W();
            int h = _mineral->H();
            for (int i=_mineral->X();i<_mineral->X()+w;i++) {
                for (int j=_mineral->Y();j<_mineral->Y()+h;j++) {
                    visited[i][j]=true;
                }
            }
        }
        for (auto _base : allEntities.bases) {
            int w = _base->W();
            int h = _base->H();
            for (int i=_base->X();i<_base->X()+w;i++) {
                for (int j=_base->Y();j<_base->Y()+h;j++) {
                    if (_base->RACE() == worker->RACE()) dist_to_base.push({{i,j},0});
                    visited[i][j]=true;
                }
            }
        }
        for (auto wg : allEntities.worker_generators) {
            int w = wg->W();
            int h = wg->H();
            for (int i=wg->X();i<wg->X()+w;i++) {
                for (int j=wg->Y();j<wg->Y()+h;j++) {
                    visited[i][j]=true;
                }
            }
        }
        for (auto kamikaze : allEntities.kamikazes) {
            int w = 1;
            int h = 1;
            for (int i=kamikaze->X();i<kamikaze->X()+w;i++) {
                for (int j=kamikaze->Y();j<kamikaze->Y()+h;j++) {
                    visited[i][j]=true;
                }
            }
        }
        for (auto st : allEntities.skills_structures) {
            int w = st->W();
            int h = st->H();
            for (int i=st->X();i<st->X()+w;i++) {
                for (int j=st->Y();j<st->Y()+h;j++) {
                    visited[i][j]=true;
                }
            }
        }
        for (auto sg : allEntities.soldier_generators) {
            int w = sg->W();
            int h = sg->H();
            for (int i=sg->X();i<sg->X()+w;i++) {
                for (int j=sg->Y();j<sg->Y()+h;j++) {
                    visited[i][j]=true;
                }
            }
        }
        for (auto _worker : allEntities.workers) {
            if (worker->ID() != _worker->ID()) visited[_worker->X()][_worker->Y()] = true;
        }
        for (auto _soldier : allEntities.soldiers) {
            visited[_soldier->X()][_soldier->Y()] = true;
        }
        while (!dist_to_base.empty()) {
            auto dist = dist_to_base.front();
            distance[dist.first.first][dist.first.second] = dist.second;
            dist_to_base.pop();
            if (dist.first.first>LEFT_MAP && !visited[dist.first.first-1][dist.first.second]) {
                visited[dist.first.first-1][dist.first.second] = true;
                dist_to_base.push({{dist.first.first-1,dist.first.second},dist.second+1});
            } 
            if (dist.first.first<RIGHT_MAP && !visited[dist.first.first+1][dist.first.second]) {
                visited[dist.first.first+1][dist.first.second] = true;
                dist_to_base.push({{dist.first.first+1,dist.first.second},dist.second+1});
            } 
            if (dist.first.second>TOP_MAP && !visited[dist.first.first][dist.first.second-1]) {
                visited[dist.first.first][dist.first.second-1] = true;
                dist_to_base.push({{dist.first.first,dist.first.second-1},dist.second+1});
            } 
            if (dist.first.second<BOT_MAP && !visited[dist.first.first][dist.first.second+1]) {
                visited[dist.first.first][dist.first.second+1] = true;
                dist_to_base.push({{dist.first.first,dist.first.second+1},dist.second+1});
            } 
        }
        int myDistance = distance[worker->X()][worker->Y()];
        bool moved = false;
        if (myDistance <= 1) {
            for (auto _base : allEntities.bases)if (_base->RACE() == worker->RACE()) {
                _base->addGold(worker->GOLD());
                worker->setGold(0);
                worker->paint();
                return;
            }
            
        } 
        if (worker->X()>LEFT_MAP && distance[worker->X()-1][worker->Y()] < myDistance) {
            myDistance = distance[worker->X()-1][worker->Y()];
            moved = true;
        } 
        if (worker->X()<RIGHT_MAP && distance[worker->X()+1][worker->Y()] < myDistance) {
            myDistance = distance[worker->X()+1][worker->Y()];
            moved = true;
        } 
        if (worker->Y()>TOP_MAP && distance[worker->X()][worker->Y()-1] < myDistance) {
            myDistance = distance[worker->X()][worker->Y()-1];
            moved = true;
        }
        if (worker->Y()<BOT_MAP && distance[worker->X()][worker->Y()+1] < myDistance) {
            myDistance = distance[worker->X()][worker->Y()+1];
            moved = true;
        } 
        if (!moved) {
            worker->paint();
            return;
        }
        if (worker->X()>LEFT_MAP && distance[worker->X()-1][worker->Y()] == myDistance) {
            worker->setX(worker->X()-1);
        } else if (worker->X()<RIGHT_MAP && distance[worker->X()+1][worker->Y()] == myDistance) {
            worker->setX(worker->X()+1);
        } else if (worker->Y()>TOP_MAP && distance[worker->X()][worker->Y()-1] == myDistance) {
            worker->setY(worker->Y()-1);
        } else if (worker->Y()<BOT_MAP && distance[worker->X()][worker->Y()+1] == myDistance) {
            worker->setY(worker->Y()+1);   
        }
        worker->paint(); 
    } 
}

void moveSoldier(Soldier* soldier, entities &allEntities)
{
    soldier->erase();
    bool visited[150][40];
    int distance[150][40];
    for (int i=0;i<150;i++) {
        for (int j=0;j<40;j++) distance[i][j] = inf;
    }
    for (int i=LEFT_MAP;i<=RIGHT_MAP;i++) {
        for (int j=TOP_MAP;j<=BOT_MAP;j++) visited[i][j] = false;
    }

    queue<pair<pair<int,int> ,int> > dist_to_worker;
    for (auto _mineral : allEntities.minerals) {
        int w = _mineral->W();
        int h = _mineral->H();
        for (int i=_mineral->X();i<_mineral->X()+w;i++) {
            for (int j=_mineral->Y();j<_mineral->Y()+h;j++) {
                visited[i][j]=true;
            }
        }
    }
    for (auto _base : allEntities.bases) {
        int w = _base->W();
        int h = _base->H();
        for (int i=_base->X();i<_base->X()+w;i++) {
            for (int j=_base->Y();j<_base->Y()+h;j++) {
                visited[i][j]=true;
            }
        }
    }
    for (auto wg : allEntities.worker_generators) {
        int w = wg->W();
        int h = wg->H();
        for (int i=wg->X();i<wg->X()+w;i++) {
            for (int j=wg->Y();j<wg->Y()+h;j++) {
                visited[i][j]=true;
            }
        }
    }
    for (auto sg : allEntities.soldier_generators) {
        int w = sg->W();
        int h = sg->H();
        for (int i=sg->X();i<sg->X()+w;i++) {
            for (int j=sg->Y();j<sg->Y()+h;j++) {
                visited[i][j]=true;
            }
        }
    }
    for (auto st : allEntities.skills_structures) {
        int w = st->W();
        int h = st->H();
        for (int i=st->X();i<st->X()+w;i++) {
            for (int j=st->Y();j<st->Y()+h;j++) {
                visited[i][j]=true;
            }
        }
    }
        for (auto kamikaze : allEntities.kamikazes) {
            int w = 1;
            int h = 1;
            for (int i=kamikaze->X();i<kamikaze->X()+w;i++) {
                for (int j=kamikaze->Y();j<kamikaze->Y()+h;j++) {
                    if (kamikaze->RACE() != soldier->RACE()) dist_to_worker.push({{kamikaze->X(),kamikaze->Y()},0});
                    visited[i][j]=true;
                }
            }
        }
    for (auto _worker : allEntities.workers) {
        if (_worker->RACE() != soldier->RACE()) dist_to_worker.push({{_worker->X(),_worker->Y()},0});
        visited[_worker->X()][_worker->Y()] = true;
    }
    for (auto _soldier : allEntities.soldiers) {
        if (_soldier->RACE() != soldier->RACE()) dist_to_worker.push({{_soldier->X(),_soldier->Y()},0});
        if (soldier->ID() != _soldier->ID())visited[_soldier->X()][_soldier->Y()] = true;
    }
        while (!dist_to_worker.empty()) {
            auto dist = dist_to_worker.front();
            distance[dist.first.first][dist.first.second] = dist.second;
            dist_to_worker.pop();
            if (dist.first.first>LEFT_MAP && !visited[dist.first.first-1][dist.first.second]) {
                visited[dist.first.first-1][dist.first.second] = true;
                dist_to_worker.push({{dist.first.first-1,dist.first.second},dist.second+1});
            } 
            if (dist.first.first<RIGHT_MAP && !visited[dist.first.first+1][dist.first.second]) {
                visited[dist.first.first+1][dist.first.second] = true;
                dist_to_worker.push({{dist.first.first+1,dist.first.second},dist.second+1});
            } 
            if (dist.first.second>TOP_MAP && !visited[dist.first.first][dist.first.second-1]) {
                visited[dist.first.first][dist.first.second-1] = true;
                dist_to_worker.push({{dist.first.first,dist.first.second-1},dist.second+1});
            } 
            if (dist.first.second<BOT_MAP && !visited[dist.first.first][dist.first.second+1]) {
                visited[dist.first.first][dist.first.second+1] = true;
                dist_to_worker.push({{dist.first.first,dist.first.second+1},dist.second+1});
            } 
        }
        int myDistance = distance[soldier->X()][soldier->Y()];
        if (myDistance == 1) {
            for (int i=0;i<allEntities.workers.size();i++) {
                if (allEntities.workers[i]->RACE() != soldier->RACE() && allEntities.workers[i]->getHitBox().shareSide(soldier->getHitBox())) {
                    if (soldier->DAMAGE() >= allEntities.workers[i]->HEALTH()) {
                        allEntities.workers[i]->erase();
                        allEntities.workers.erase(allEntities.workers.begin()+i);
                        i=0;
                    }
                }
            }
            for (int i=0;i<allEntities.workers.size();i++) {
                if (allEntities.workers[i]->RACE() != soldier->RACE() && allEntities.workers[i]->getHitBox().shareSide(soldier->getHitBox())) {
                    allEntities.workers[i]->setHealth(allEntities.workers[i]->HEALTH()-soldier->DAMAGE());
                }
            }

            for (int i=0;i<allEntities.kamikazes.size();i++) {
                if (allEntities.kamikazes[i]->RACE() != soldier->RACE() && allEntities.kamikazes[i]->getHitBox().shareSide(soldier->getHitBox())) {
                    if (soldier->DAMAGE() >= allEntities.kamikazes[i]->HEALTH()) {
                        allEntities.kamikazes[i]->erase();
                        allEntities.kamikazes.erase(allEntities.kamikazes.begin()+i);
                        i=0;
                    }
                }
            }
            for (int i=0;i<allEntities.kamikazes.size();i++) {
                if (allEntities.kamikazes[i]->RACE() != soldier->RACE() && allEntities.kamikazes[i]->getHitBox().shareSide(soldier->getHitBox())) {
                    allEntities.kamikazes[i]->setHealth(allEntities.kamikazes[i]->HEALTH()-soldier->DAMAGE());
                }
            }

            int myDamage = 0;
            for (int i=0;i<allEntities.soldiers.size();i++) if (allEntities.soldiers[i]->RACE() != soldier->RACE()) {
                if (allEntities.soldiers[i]->getHitBox().shareSide(soldier->getHitBox())) {
                   if (soldier->DAMAGE() >= allEntities.soldiers[i]->HEALTH()) {
                        allEntities.soldiers[i]->erase();
                        myDamage += allEntities.soldiers[i]->DAMAGE();
                        allEntities.soldiers.erase(allEntities.soldiers.begin()+i);
                        i=0;
                    } else {
                        myDamage += allEntities.soldiers[i]->DAMAGE();
                    }
                }
            }
            for (int i=0;i<allEntities.soldiers.size();i++) if (allEntities.soldiers[i]->RACE() != soldier->RACE()) {
                if (allEntities.soldiers[i]->getHitBox().shareSide(soldier->getHitBox())) {
                   allEntities.soldiers[i]->setHealth(allEntities.soldiers[i]->HEALTH()-soldier->DAMAGE());
                }
            }
            if (myDamage >= soldier->HEALTH()) {
                int id = soldier->ID();
                for (int i=0;i<allEntities.soldiers.size();i++) {
                    if (allEntities.soldiers[i]->ID() == id) {
                        allEntities.soldiers[i]->erase();
                        allEntities.soldiers.erase(allEntities.soldiers.begin()+i);
                        i=0;
                    }
                }
            } else {
                soldier->setHealth(soldier->HEALTH() - myDamage);
                soldier->paint();
            }
            return;
        }
        bool moved = false;
        if (soldier->X()>LEFT_MAP && distance[soldier->X()-1][soldier->Y()] < myDistance) {
            myDistance = distance[soldier->X()-1][soldier->Y()];
            moved = true;
        } 
        if (soldier->X()<RIGHT_MAP && distance[soldier->X()+1][soldier->Y()] < myDistance) {
            myDistance = distance[soldier->X()+1][soldier->Y()];
            moved = true;
        } 
        if (soldier->Y()>TOP_MAP && distance[soldier->X()][soldier->Y()-1] < myDistance) {
            myDistance = distance[soldier->X()][soldier->Y()-1];
            moved = true;
        }
        if (soldier->Y()<BOT_MAP && distance[soldier->X()][soldier->Y()+1] < myDistance) {
            myDistance = distance[soldier->X()][soldier->Y()+1];
            moved = true;
        } 
        if (!moved) {
            soldier->paint();
            return;
        }
        if (soldier->X()>LEFT_MAP && distance[soldier->X()-1][soldier->Y()] == myDistance) {
            soldier->setX(soldier->X()-1);
        } else if (soldier->X()<RIGHT_MAP && distance[soldier->X()+1][soldier->Y()] == myDistance) {
            soldier->setX(soldier->X()+1);
        } else if (soldier->Y()>TOP_MAP && distance[soldier->X()][soldier->Y()-1] == myDistance) {
            soldier->setY(soldier->Y()-1);
        } else if (soldier->Y()<BOT_MAP && distance[soldier->X()][soldier->Y()+1] == myDistance) {
            soldier->setY(soldier->Y()+1);   
        }
        soldier->paint();
}
