#include "consts.h"
#include "writer.h"
#include "Entities.h"

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
    while (!game_over) {

    }
    return 0;
}