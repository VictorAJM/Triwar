///TODO:


#include "consts.h"
#include "writer.h"
#include "Entities.h" 
#include "hitBox.h"
#include "Movements.h"
#include "Actions.hpp"
#include "Endgame.h"
#include "StatsBar.h"
#include "Area_Random.hpp"
void *functionCount(void *);
int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}
bool is_Empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

int main()
{
    initscr();
     start_color();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, true);
       nodelay(stdscr, TRUE);

    scrollok(stdscr, TRUE);
    srand(time(NULL));
    crearCharMatrix();
    
    colors.push_back(init_pair(3, COLOR_RED, COLOR_BLACK));
    colors.push_back(init_pair(1, COLOR_GREEN, COLOR_BLACK));
    colors.push_back(init_pair(2, COLOR_BLUE, COLOR_BLACK));
    colors.push_back(init_pair(4, COLOR_YELLOW, COLOR_BLACK));
    colors.push_back(init_pair(5, COLOR_WHITE, COLOR_WHITE));
    bool game_over = false;
    ifstream fin;
    entities allEntities;
    ofstream ferase;
   
        
        try {
        fin.open("data.txt");
 
        if (!fin) {

        }
        if (!is_Empty(fin)) {
            int n;
            fin >> n;
            
            for (int i=0;i<n;i++) {
                string type;
                char race;
                int x,y,w,h,he,da;
                
                fin >> type;
                if (type=="W") {
                    fin >> race >> x >> y >> h >> he;
                    Worker* w = new Worker(x,y,race);
                    w->setDamage(he);
                    w->setHealth(h);
                    w->paint();
                    allEntities.workers.push_back(w);
                } else if (type=="S") {
                    fin >> race >> x >> y >> h >> he;
                    Soldier* w = new Soldier(x,y,race);
                    w->setDamage(he);
                    w->setHealth(h);
                    w->paint();
                    allEntities.soldiers.push_back(w);
                } else if (type=="B") {
                    fin >> race >> x >> y >> w >> h;
                    Base* base = new Base(x,y,race);
                    base->paint();
                    allEntities.bases.push_back(base);
                } else if (type=="M") {
                    fin >> race >> x >> y >> w >> h;
                    Mineral* m = new Mineral(x,y);
                    m->paint();
                    allEntities.minerals.push_back(m);
                } else if (type=="Q") {
                    fin >> race >> x >> y >> w >> h;
                    Worker_Generator* wg = new Worker_Generator(x,y,race);
                    wg->paint();
                    allEntities.worker_generators.push_back(wg);
                } else if (type=="E") {
                    fin >> race >> x >> y >> w >> h;
                    Soldier_Generator* wg = new Soldier_Generator(x,y,race);
                    wg->paint();
                    allEntities.soldier_generators.push_back(wg);
                } else if (type=="K") {
                    fin >> race >> x >> y >> h >> he;
                    Kamikaze* k = new Kamikaze(x,y,race);
                    k->setDamage(he);
                    k->setHealth(h);
                    k->paint();
                    allEntities.kamikazes.push_back(k);
                } else if (type=="R") {
                    fin >> race >> x >> y >> w >> h;
                    Skills_Structure* wg = new Skills_Structure(x,y,race);
                    wg->paint();
                    allEntities.skills_structures.push_back(wg);
                }
                drawStats(allEntities);
                
            }
            fin >> timeCounter;
            fin.close();
        } else {
            for (int i=0;i<3;i++) {
                pair<int,int> coords = AreaRandom::getPosition(10,10,allEntities);
                allEntities.bases.push_back(new Base(coords.first,coords.second,'a'+i));
            }

            for (int i=0;i<15;i++) {
                pair<int,int> coords = AreaRandom::getPosition(3,3, allEntities);
                allEntities.minerals.push_back(new Mineral(coords.first,coords.second));
            }
            

            for (int i=0;i<5;i++) {
                for (auto base : allEntities.bases) {
                    allEntities.workers.push_back(new Worker(base->X()+i,base->Y()-1,base->RACE()));
                }
            }
            for (auto _base : allEntities.bases) _base->paint();
            for (auto _worker : allEntities.workers) _worker->paint();
            for (auto mineral : allEntities.minerals) mineral->paint();
            drawStats(allEntities);
        }
    } catch(...) {
        for (int i=0;i<3;i++) {
            pair<int,int> coords = AreaRandom::getPosition(10,10,allEntities);
            allEntities.bases.push_back(new Base(coords.first,coords.second,'a'+i));
        }

        for (int i=0;i<15;i++) {
            pair<int,int> coords = AreaRandom::getPosition(3,3, allEntities);
            allEntities.minerals.push_back(new Mineral(coords.first,coords.second));
        }
        for (int i=0;i<5;i++) {
            for (auto base : allEntities.bases) {
                allEntities.workers.push_back(new Worker(base->X()+i,base->Y()-1,base->RACE()));
            }
        }
        for (auto _base : allEntities.bases) _base->paint();
        for (auto _worker : allEntities.workers) _worker->paint();
        for (auto mineral : allEntities.minerals) mineral->paint();
        drawStats(allEntities);
    }
    

    pthread_t timeThread;
    pthread_create(&timeThread, NULL, &functionCount, (void*)game_over);
    ocultarCursor();
    pintar_limites();
    while (!game_over) {
        int c;
        if (kbhit()) {

                int ch = getch();
                if (ch == 's') {
                game_over = true;
                // guardar
                int n = 0;
                ofstream fout;
	            fout.open("data.txt");
                for (auto w : allEntities.workers) n++;
                for (auto b : allEntities.bases) n++;
                for (auto s : allEntities.soldiers) n++;
                for (auto k : allEntities.kamikazes) n++;
                for (auto wg : allEntities.worker_generators) n++;
                for (auto m : allEntities.minerals) n++;
                for (auto sg : allEntities.soldier_generators) n++;
                for (auto st : allEntities.skills_structures) n++;
                fout << n << "\n";
                for (auto w : allEntities.workers) fout << w->getInfo() << "\n";
                for (auto b : allEntities.bases) fout << b->getInfo() << "\n";
                for (auto s : allEntities.soldiers) fout << s->getInfo() << "\n";
                for (auto k : allEntities.kamikazes) fout << k->getInfo() << "\n";
                for (auto wg : allEntities.worker_generators) fout << wg->getInfo() << "\n";
                for (auto m : allEntities.minerals) fout << m->getInfo() << "\n";
                for (auto sg : allEntities.soldier_generators) fout << sg->getInfo() << "\n";
                for (auto st : allEntities.skills_structures) fout << st->getInfo() << "\n";
                fout << timeCounter<<"\n";
                return 0;
                }
        }
        for (auto st : allEntities.skills_structures) {
            if (st->CD() == 0 ) {
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
                    try {
        sleep(MICRO_DURATION);
        } catch(...) {
            
        }
        }
        for (auto _soldier : allEntities.soldiers) {
            moveSoldier(_soldier, allEntities);
            drawStats(allEntities);
            getWinner(allEntities);
                    try {
        sleep(MICRO_DURATION);
        } catch(...) {
            
        }
        }
        for (auto _base : allEntities.bases) {
            actionBase(_base, allEntities);
            getWinner(allEntities);
            drawStats(allEntities);
        }

        game_over = getWinner(allEntities);
                    try {
        sleep(MICRO_DURATION);
        } catch(...) {
            
        }
    }
    return 0;
}
void *functionCount(void *ptr)
{
    bool a;
    a=(bool)ptr;
    for (;;) {
        pthread_mutex_lock(&count_mutex);
        timeCounter++;
        pthread_mutex_unlock(&count_mutex);
        
        if (a == true) return(NULL);
        try {
            sleep(1);
        } catch(...) {
            
        }
    }
}