#pragma once
#ifndef BASICATTACK_H
#define BASICATTACK_H
#include <vector>
#include "Action.h"
#include "Unit.h"

class TheMOSTBasicHit : public Action
{
public:
    TheMOSTBasicHit(); // Make sure this is here
    virtual void Execute(Unit* caster, vector<Unit*>& goodGuys, vector<Unit*>& badGuys) override;
};

#endif

