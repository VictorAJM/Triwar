#include "consts.h"
#include "Entities.h"
#include "hitBox.h"
namespace AreaRandom {
    pair<int,int> getPosition(int x, int y, vector<Base*> &bases, vector<Worker*> &workers, vector<Soldier*> &soldiers, vector<Mineral*> &minerals)
    {
        vector<pair<int,int> > possible_positions;
        for (int i=LEFT_MAP+2;i<RIGHT_MAP-x-1;i++) {
            for (int j=TOP_MAP+2;j<BOT_MAP-y-1;j++) {
                bool free = true;
                for (auto base : bases) if (hitBox(i-1,j-1,x+2,y+2).collisionWith(base->getHitBox())) free = false;
                for (auto worker : workers) if (hitBox(i-1,j-1,x+2,y+2).collisionWith(worker->getHitBox())) free = false;
                for (auto soldier : soldiers) if (hitBox(i-1,j-1,x+2,y+2).collisionWith(soldier->getHitBox())) free = false;
                for (auto mineral : minerals) if (hitBox(i-1,j-1,x+2,y+2).collisionWith(mineral->getHitBox())) free = false;
                if (free) possible_positions.push_back(make_pair(i,j));
            }
        }
        if (possible_positions.size()==0) return make_pair(0,0);
        return possible_positions[rand()%(possible_positions.size())];
    }
    pair<int,int> getPosition(int x, int y, entities &allEntities) 
    {
        vector<pair<int,int> > possible_positions;
        for (int i=LEFT_MAP+2;i<RIGHT_MAP-x-1;i++) {
            for (int j=TOP_MAP+2;j<BOT_MAP-y-1;j++) {
                bool free = true;
                for (auto base : allEntities.bases) if (hitBox(i-1,j-1,x+2,y+2).collisionWith(base->getHitBox())) free = false;
                for (auto worker : allEntities.workers) if (hitBox(i-1,j-1,x+2,y+2).collisionWith(worker->getHitBox())) free = false;
                for (auto soldier : allEntities.soldiers) if (hitBox(i-1,j-1,x+2,y+2).collisionWith(soldier->getHitBox())) free = false;
                for (auto mineral : allEntities.minerals) if (hitBox(i-1,j-1,x+2,y+2).collisionWith(mineral->getHitBox())) free = false;
                if (free) possible_positions.push_back(make_pair(i,j));
            }
        }
        if (possible_positions.size()==0) return make_pair(0,0);
        return possible_positions[rand()%(possible_positions.size())];
    }
}