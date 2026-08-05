#pragma once
#ifndef SINGLETARGETATTACK_H
#define SINGLETARGETATTACK_H

#include "Action.h"
#include <vector>
class SCREWYouInPARTICULAR : public Action
{
public:
    SCREWYouInPARTICULAR(string skillName);
    void Execute(Unit* caster, vector<Unit*>& goodGuys,vector<Unit*>& badGuys) override;
};
#endif
