#pragma once
#include "Entity.h"
#include "Structure.h"
#include "Base.h"
#include "Mineral.h"
#include "Unit.h"
#include "Worker.h"
#include "Soldier.h"
#include "Generators.hpp"

struct entities {
    vector<Base*> bases;
    vector<Worker*> workers;
    vector<Soldier*> soldiers;
    vector<Mineral*> minerals;
    //
};