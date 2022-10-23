#pragma once
#include "Entity.h"
#include "Structure.h"
#include "Base.h"
#include "Mineral.h"
#include "Unit.h"
#include "Worker.h"
#include "Soldier.h"
#include "Generators.hpp"
#include "Skills_Structure.hpp"
#include "Kamikaze.hpp"
struct entities {
    vector<Base*> bases;
    vector<Worker*> workers;
    vector<Soldier*> soldiers;
    vector<Mineral*> minerals;
    vector<Worker_Generator*> worker_generators;
    vector<Soldier_Generator*> soldier_generators;
    vector<Skills_Structure*> skills_structures;
    vector<Kamikaze*> kamikazes;
};