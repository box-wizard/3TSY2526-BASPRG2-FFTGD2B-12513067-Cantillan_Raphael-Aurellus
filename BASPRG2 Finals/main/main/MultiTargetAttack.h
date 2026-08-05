#pragma once
#ifndef MULTITARGETATTACK_H
#define MULTITARGETATTACK_H

#include "Action.h"
#include <vector>
class KILLSALLOFYOU : public Action
{
public:
    KILLSALLOFYOU(string skillName);
    void Execute(Unit* caster, vector<Unit*>& goodGuys,vector<Unit*>& badGuys) override;
};
#endif

