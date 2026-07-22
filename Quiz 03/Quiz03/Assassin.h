#ifndef ASSASSIN_H
#define ASSASSIN_H

#include "Unit.h"

class Assassin : public Unit {
public:
    Assassin(string uName) : Unit(uName, UnitClass::Assassin, 100, 25, 8, 25, 25) {}
};

#endif