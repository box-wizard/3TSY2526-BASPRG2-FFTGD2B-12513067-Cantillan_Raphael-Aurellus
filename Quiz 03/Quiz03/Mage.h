#ifndef MAGE_H
#define MAGE_H

#include "Unit.h"

class Mage : public Unit {
public:
    Mage(string uName) : Unit(uName, UnitClass::Mage, 120, 30, 10, 12, 18) {}
};

#endif