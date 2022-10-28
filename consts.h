#pragma once
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <time.h>
#include <ncurses.h>
#include <curses.h>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <sstream> 

#define LEFT_MAP 3
#define RIGHT_MAP 146
#define TOP_MAP 4
#define BOT_MAP 38
#define MICRO_DURATION 0

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN 0x0008

#define WORKER_COST 30
#define SOLDIER_COST 70
#define WORKER_GENERATOR_COST 500
#define SOLDIER_GENERATOR_COST 900
#define SKILLS_STRUCTURE_COST 600
#define KAMIKAZE_COST 300
#define COOLDOWN_GENERATOR 100
#define CD_REDUCTION 10


pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;


using namespace std;
const int inf = 1e9+7;
vector<string> charMap;
set<int> entitiesID;
vector<int> colors;
enum colorString {
    raceA = 1,
    raceB = 2,
    raceC = 3,
    raceM = 4,
    raceL = 5
};
int timeCounter = 0;