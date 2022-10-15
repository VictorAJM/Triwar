#include "consts.h"
#include "writer.h"
#include "Entities.h"
#include "hitBox.h"
int main()
{
    srand(time(NULL));
    crearCharMatrix();
    ocultarCursor();
    pintar_limites();
    bool game_over = false;
    Base* base1 = new Base(10,10,'a');
    Base* base2 = new Base(65,25,'b');
    Base* base3 = new Base(120,10,'c');
    base1->paint(); base2->paint(); base3->paint();
    vector<Mineral*> minerals;
    for (int i=0;i<5;i++) {
        int x,y;
        bool choque = false;
        do {
            x = rand()%130+5;
            y = rand()%30+5;
            hitBox thisHitBox(x,y,3,3);
            if (thisHitBox.collisionWith(base1->getHitBox())) choque = true;
            if (thisHitBox.collisionWith(base2->getHitBox())) choque = true;
            if (thisHitBox.collisionWith(base3->getHitBox())) choque = true;
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
    Sleep(1000);
    for (auto _worker : workers) _worker->paint();
    for (auto mineral : minerals) mineral->paint();
    while (!game_over) {

    }
    return 0;
}