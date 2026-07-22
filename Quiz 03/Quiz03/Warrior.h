#ifndef WARRIOR_H
#define WARRIOR_H

#include "Unit.h"

class Warrior : public Unit {
public:
    Warrior(string uName) : Unit(uName, UnitClass::Warrior, 150, 20, 15, 10, 15) {}
};

#endif