#pragma once
#include "things/Entity.h"
#include "things/Structure.h"
#include "things/Base.h"
#include "things/Mineral.h"
#include "things/Unit.h"
#include "things/Worker.h"
#include "things/Soldier.h"
#include "things/Generators.hpp"
#include "things/Skills_Structure.hpp"
#include "things/Kamikaze.hpp"
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