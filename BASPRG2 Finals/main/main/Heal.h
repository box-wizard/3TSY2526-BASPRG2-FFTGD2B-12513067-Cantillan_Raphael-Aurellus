#pragma once
#ifndef HEAL_H
#define HEAL_H

#include "Action.h"
#include <vector>
class RestoresHEALTH : public Action
{
public:
    RestoresHEALTH (string skillName);
    void Execute(Unit* caster, vector<Unit*>& goodGuys,vector<Unit*>& badGuys) override;
};
#endif

