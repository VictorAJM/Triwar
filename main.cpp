///TODO:
// improve Action Chooser
// Kamikazes are not working properly
// add Loco
// Add threads to the last Structures Units and Skills
// Save current state of game in files
// Import/Export current state

// FINISH :)


#include "consts.h"
#include "writer.h"
#include "Entities.h" 
#include "hitBox.h"
#include "Movements.h"
#include "Actions.hpp"
#include "Endgame.h"
#include "StatsBar.h"
#include "Area_Random.hpp"
int main()
{
    srand(time(NULL));
    crearCharMatrix();
    ocultarCursor();
    pintar_limites();
    bool game_over = false;

    entities allEntities;
    for (int i=0;i<3;i++) {
        pair<int,int> coords = AreaRandom::getPosition(10,10,allEntities);
        allEntities.bases.push_back(new Base(coords.first,coords.second,'a'+i));
    }

    for (int i=0;i<15;i++) {
        pair<int,int> coords = AreaRandom::getPosition(3,3, allEntities);
        allEntities.minerals.push_back(new Mineral(coords.first,coords.second));
    }
    Sleep(1000);

    for (int i=0;i<5;i++) {
        for (auto base : allEntities.bases) {
            allEntities.workers.push_back(new Worker(base->X()+i,base->Y()-1,base->RACE()));
        }
    }
    for (auto _base : allEntities.bases) _base->paint();
    for (auto _worker : allEntities.workers) _worker->paint();
    for (auto mineral : allEntities.minerals) mineral->paint();
    drawStats(allEntities);
    while (!game_over) {
        for (auto& st : allEntities.skills_structures) {
            if (st->CD() == 0 ) {
                int skill = st->SKILL();
                int race = st->RACE();
                actionSkill(st, allEntities);
                st->setCD(COOLDOWN_GENERATOR);
                st->setSkill();
                getWinner(allEntities);
            }
            st->setCD(st->CD()-CD_REDUCTION);
        }
        for (auto wg : allEntities.worker_generators) {
            if (wg->CD() == 0) {
                // new worker
                vector<pair<int,int> > positions = AreaRandom::positionAround(wg,allEntities);
                if (positions.size()>0) {
                    int pos = rand()%(positions.size());
                    Worker* newWorker = new Worker(positions[pos].first,positions[pos].second,wg->RACE());
                    newWorker->setHealth(newWorker->HEALTH()+wg->getHealth());
                    newWorker->setDamage(newWorker->HEALTH()+wg->getDamage());
                    newWorker->paint();
                    allEntities.workers.push_back(newWorker);
                    drawStats(allEntities);
                }
                wg->setCD(COOLDOWN_GENERATOR);
                getWinner(allEntities);
            } 
            wg->setCD(wg->CD()-CD_REDUCTION);
        }
        for (auto sg : allEntities.soldier_generators) {
            if (sg->CD() == 0) {
                // new soldier
                vector<pair<int,int> > positions = AreaRandom::positionAround(sg,allEntities);
                if (positions.size()>0) {
                    int pos = rand()%(positions.size());
                    Soldier* newSoldier = new Soldier(positions[pos].first,positions[pos].second,sg->RACE());
                    newSoldier->setHealth(newSoldier->HEALTH()+sg->getHealth());
                    newSoldier->setDamage(newSoldier->HEALTH()+sg->getDamage());
                    newSoldier->paint();
                    allEntities.soldiers.push_back(newSoldier);
                    drawStats(allEntities);
                }
                getWinner(allEntities);
                sg->setCD(COOLDOWN_GENERATOR);
            }
            sg->setCD(sg->CD()-CD_REDUCTION);
        }
        for (auto _kamikaze : allEntities.kamikazes) {
            moveKamikaze(_kamikaze, allEntities);
            drawStats(allEntities);
            getWinner(allEntities);
        }
        for (auto _worker : allEntities.workers) {
            moveWorker(_worker, allEntities);
            drawStats(allEntities);
            getWinner(allEntities);
            Sleep(MICRO_DURATION);
        }
        for (auto _soldier : allEntities.soldiers) {
            moveSoldier(_soldier, allEntities);
            drawStats(allEntities);
            getWinner(allEntities);
            Sleep(MICRO_DURATION);
        }
        for (auto _base : allEntities.bases) {
            actionBase(_base, allEntities);
            getWinner(allEntities);
            drawStats(allEntities);
        }

        game_over = getWinner(allEntities);
        Sleep(MICRO_DURATION);
    }
    return 0;
}