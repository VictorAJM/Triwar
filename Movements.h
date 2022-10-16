#pragma once
#include "consts.h"
#include "Entities.h"

void moveWorker(Worker* worker, vector<Worker*> workers, vector<Mineral*> minerals,vector<Base*> bases, vector<Soldier*> soldiers) 
{
    worker->erase();
    if (worker->GOLD() == 0) {
        bool visited[150][40];
        int distance[150][40];
        const int inf = 1e9+7;
        for (int i=0;i<150;i++) {
            for (int j=0;j<40;j++) distance[i][j] = inf;
        }
        for (int i=LEFT_MAP;i<=RIGHT_MAP;i++) {
            for (int j=TOP_MAP;j<=BOT_MAP;j++) visited[i][j] = false;
        }
        queue<pair<pair<int,int> ,int> > dist_to_mineral;
        for (auto _mineral : minerals) {
            int w = _mineral->W();
            int h = _mineral->H();
            for (int i=_mineral->X();i<_mineral->X()+w;i++) {
                for (int j=_mineral->Y();j<_mineral->Y()+h;j++) {
                    dist_to_mineral.push({{i,j},0});
                    visited[i][j]=true;
                }
            }
        }
        for (auto _base : bases) {
            int w = _base->W();
            int h = _base->H();
            for (int i=_base->X();i<_base->X()+w;i++) {
                for (int j=_base->Y();j<_base->Y()+h;j++) {
                    visited[i][j]=true;
                }
            }
        }
        for (auto _worker : workers) {
            visited[_worker->X()][_worker->Y()] = true;
        }
        for (auto _soldier : soldiers) {
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
            worker->setGold(50);
            return;
        } 
        if (worker->X()>LEFT_MAP && distance[worker->X()-1][worker->Y()] < myDistance) {
            myDistance = distance[worker->X()-1][worker->Y()];
        } 
        if (worker->X()<RIGHT_MAP && distance[worker->X()+1][worker->Y()] < myDistance) {
            myDistance = distance[worker->X()+1][worker->Y()];
        } 
        if (worker->Y()>TOP_MAP && distance[worker->X()][worker->Y()-1] < myDistance) {
            myDistance = distance[worker->X()][worker->Y()-1];
        } 
        if (worker->Y()<BOT_MAP && distance[worker->X()][worker->Y()+1] < myDistance) {
            myDistance = distance[worker->X()][worker->Y()+1];
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
        const int inf = 1e9+7;
        for (int i=0;i<150;i++) {
            for (int j=0;j<40;j++) distance[i][j] = inf;
        }
        for (int i=LEFT_MAP;i<=RIGHT_MAP;i++) {
            for (int j=TOP_MAP;j<=BOT_MAP;j++) visited[i][j] = false;
        }
        
        queue<pair<pair<int,int> ,int> > dist_to_base;
        for (auto _mineral : minerals) {
            int w = _mineral->W();
            int h = _mineral->H();
            for (int i=_mineral->X();i<_mineral->X()+w;i++) {
                for (int j=_mineral->Y();j<_mineral->Y()+h;j++) {
                    visited[i][j]=true;
                }
            }
        }
        for (auto _base : bases) {
            int w = _base->W();
            int h = _base->H();
            for (int i=_base->X();i<_base->X()+w;i++) {
                for (int j=_base->Y();j<_base->Y()+h;j++) {
                    if (_base->RACE() == worker->RACE()) dist_to_base.push({{i,j},0});
                    visited[i][j]=true;
                }
            }
        }
        for (auto _worker : workers) {
            visited[_worker->X()][_worker->Y()] = true;
        }
        for (auto _soldier : soldiers) {
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
        if (myDistance <= 1) {
            for (auto _base : bases)if (_base->RACE() == worker->RACE()) {
                worker->setGold(0);
                _base->addGold(50);
                worker->paint();
                return;
            }
            
        } 
        if (worker->X()>LEFT_MAP && distance[worker->X()-1][worker->Y()] < myDistance) {
            myDistance = distance[worker->X()-1][worker->Y()];
        } 
        if (worker->X()<RIGHT_MAP && distance[worker->X()+1][worker->Y()] < myDistance) {
            myDistance = distance[worker->X()+1][worker->Y()];
        } 
        if (worker->Y()>TOP_MAP && distance[worker->X()][worker->Y()-1] < myDistance) {
            myDistance = distance[worker->X()][worker->Y()-1];
        }
        if (worker->Y()<BOT_MAP && distance[worker->X()][worker->Y()+1] < myDistance) {
            myDistance = distance[worker->X()][worker->Y()+1];
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


void moveSoldier(Soldier* soldier, vector<Worker*> workers, vector<Mineral*> minerals, vector<Base*> bases, vector<Soldier*> soldiers)
{
    soldier->erase();
    bool visited[150][40];
    int distance[150][40];
    const int inf = 1e9+7;
    for (int i=0;i<150;i++) {
        for (int j=0;j<40;j++) distance[i][j] = inf;
    }
    for (int i=LEFT_MAP;i<=RIGHT_MAP;i++) {
        for (int j=TOP_MAP;j<=BOT_MAP;j++) visited[i][j] = false;
    }

    queue<pair<pair<int,int> ,int> > dist_to_worker;
    for (auto _mineral : minerals) {
        int w = _mineral->W();
        int h = _mineral->H();
        for (int i=_mineral->X();i<_mineral->X()+w;i++) {
            for (int j=_mineral->Y();j<_mineral->Y()+h;j++) {
                visited[i][j]=true;
            }
        }
    }
    for (auto _base : bases) {
        int w = _base->W();
        int h = _base->H();
        for (int i=_base->X();i<_base->X()+w;i++) {
            for (int j=_base->Y();j<_base->Y()+h;j++) {
                visited[i][j]=true;
            }
        }
    }
    for (auto _worker : workers) {
        if (_worker->RACE() != soldier->RACE()) dist_to_worker.push({{_worker->X(),_worker->Y()},0});
        visited[_worker->X()][_worker->Y()] = true;
    }
    for (auto _soldier : soldiers) {
        visited[_soldier->X()][_soldier->Y()] = true;
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
        if (soldier->X()>LEFT_MAP && distance[soldier->X()-1][soldier->Y()] < myDistance) {
            myDistance = distance[soldier->X()-1][soldier->Y()];
        } 
        if (soldier->X()<RIGHT_MAP && distance[soldier->X()+1][soldier->Y()] < myDistance) {
            myDistance = distance[soldier->X()+1][soldier->Y()];
        } 
        if (soldier->Y()>TOP_MAP && distance[soldier->X()][soldier->Y()-1] < myDistance) {
            myDistance = distance[soldier->X()][soldier->Y()-1];
        }
        if (soldier->Y()<BOT_MAP && distance[soldier->X()][soldier->Y()+1] < myDistance) {
            myDistance = distance[soldier->X()][soldier->Y()+1];
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
        for(int i=0;i<workers.size();i++) if (soldier->getHitBox().collisionWith(workers[i]->getHitBox())) {
            workers[i]->erase();
            auto a = workers[i];
            workers.erase(workers.begin()+i);
            delete a;
            i=0;
        }
        soldier->paint(); 
}