///TODO:
// clean files
// create Unit's Structures 
// improve random chooser action
// Add Unit's Structures (working?)
// OMG luismi
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
        for (auto _worker : allEntities.workers) {
            moveWorker(_worker, allEntities);
            Sleep(MICRO_DURATION);
            drawStats(allEntities);
        }
        for (auto _soldier : allEntities.soldiers) {
            moveSoldier(_soldier, allEntities);
            Sleep(MICRO_DURATION);
            drawStats(allEntities);
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