#pragma once
#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <vector>

using namespace std;

class Unit;

class Action
{
protected:
    string initName;
    int initMPCost;
    int computeTotalDamage( Unit* attacker, Unit* target, float multiplier) const;
    bool WinRate( Unit* attacker, Unit* target) const;

public:
    Action(string name, int mpCost);
    virtual ~Action();

    virtual void Execute (Unit* caster, vector<Unit*>& goodGuys, vector<Unit*>& badGuys) = 0;
 
    string GetName() const;
    int GetMpCost() const;
};

#endif

