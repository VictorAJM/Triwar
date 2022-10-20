#pragma once
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <queue>
#include <set>
#include <map>

#define LEFT_MAP 3
#define RIGHT_MAP 146
#define TOP_MAP 4
#define BOT_MAP 38
#define MICRO_DURATION 0

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN 0x0008

using namespace std;
const int inf = 1e9+7;
vector<string> charMap;
set<int> entitiesID;
vector<string> colors = {"\x1b[31m","\x1b[32m","\x1b[34m","\x1b[33m","\x1b[0m","\x1b[107m"};
enum colorString {
    raceA = 0,
    raceB = 1,
    raceC = 2,
    raceM = 3,
    borrar = 4,
    raceV = 5
};