///TODO:
// add Units skills and statics
// Add skill's Structures
// Add threads to the last Structures Units and Skills
// Agregar colores a todo

// Save current state of game in files

// FINISH :)
#include "consts.h"
#include "writer.h"
#include "Entities.h"
#include "hitBox.h"
#include "Movements.h"
#include "Actions.h"
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
        for (auto& wg : allEntities.worker_generators) {
            if (wg->CD() == 0) {
                // new worker
                vector<pair<int,int> > positions = AreaRandom::positionAround(wg,allEntities);
                if (positions.size()>0) {
                    int pos = rand()%(positions.size());
                    Worker* newWorker = new Worker(positions[pos].first,positions[pos].second,wg->RACE());
                    newWorker->paint();
                    allEntities.workers.push_back(newWorker);
                }
                wg->setCD(60);
            } 
            wg->setCD(wg->CD()-10);
        }
        for (auto sg : allEntities.soldier_generators) {
            if (sg->CD() == 0) {
                // new soldier
                vector<pair<int,int> > positions = AreaRandom::positionAround(sg,allEntities);
                if (positions.size()>0) {
                    int pos = rand()%(positions.size());
                    Soldier* newSoldier = new Soldier(positions[pos].first,positions[pos].second,sg->RACE());
                    newSoldier->paint();
                    allEntities.soldiers.push_back(newSoldier);
                }
                sg->setCD(60);
            }
            sg->setCD(sg->CD()-10);
        }
        for (auto _worker : allEntities.workers) {
            moveWorker(_worker, allEntities);
            drawStats(allEntities);
            Sleep(MICRO_DURATION);
        }
        for (auto _soldier : allEntities.soldiers) {
            moveSoldier(_soldier, allEntities);
            drawStats(allEntities);
            Sleep(MICRO_DURATION);
        }
        for (auto _base : allEntities.bases) {
            actionBase(_base, allEntities);
            drawStats(allEntities);
        }

        game_over = getWinner(allEntities);
        Sleep(MICRO_DURATION);
    }
    return 0;
}