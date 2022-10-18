#include "consts.h"
#include "writer.h"
#include "Entities.h"
#include "hitBox.h"
#include "Movements.h"
#include "Actions.h"
#include "Endgame.h"
#include "StatsBar.h"
int main()
{
    //srand(time(NULL));
    crearCharMatrix();
    ocultarCursor();
    pintar_limites();
    bool game_over = false;
    Base* base1 = new Base(10,10,'a');
    Base* base2 = new Base(65,25,'b');
    Base* base3 = new Base(120,10,'c');

    vector<Mineral*> minerals;
    for (int i=0;i<5;i++) {
        int x,y;
        bool choque = false;
        do {
            x = rand()%128+6;
            y = rand()%28+6;
            hitBox thisHitBox(x-1,y-1,5,5);
            if (thisHitBox.collisionWith(base1->getHitBox())) choque = true;
            if (thisHitBox.collisionWith(base2->getHitBox())) choque = true;
            if (thisHitBox.collisionWith(base3->getHitBox())) choque = true;
            for (auto mineral : minerals) if (thisHitBox.collisionWith(mineral->getHitBox())) choque = true;
        } while (choque);
        minerals.push_back(new Mineral(x,y));
    }
    Sleep(1000);
    vector<Worker*> workers;
    for (int i=0;i<5;i++) {
        workers.push_back(new Worker(base1->X()+i,base1->Y()-1,'a'));
        workers.push_back(new Worker(base2->X()+i,base2->Y()-1,'b'));
        workers.push_back(new Worker(base3->X()+i,base3->Y()-1,'c'));
    }

    vector<Base*> bases;
    bases.push_back(base1); bases.push_back(base2); bases.push_back(base3);
    vector<Soldier*> soldiers;
    for (auto _base : bases) _base->paint();
    for (auto _worker : workers) _worker->paint();
    for (auto mineral : minerals) mineral->paint();
    drawStats(workers, soldiers, bases);
    while (!game_over) {
        for (auto _worker : workers) {
            moveWorker(_worker, workers, minerals, bases,soldiers);
            Sleep(MICRO_DURATION);
            drawStats(workers, soldiers, bases);
        }
        for (auto _soldier : soldiers) {
            moveSoldier(_soldier, workers, minerals, bases, soldiers);
            Sleep(MICRO_DURATION);
            drawStats(workers, soldiers, bases);
        }
        for (auto _base : bases) {
            actionBase(_base, bases, workers, soldiers, minerals);
            drawStats(workers, soldiers, bases);
        }

        game_over = getWinner(workers, soldiers, bases);
        Sleep(MICRO_DURATION);
    }
    return 0;
}