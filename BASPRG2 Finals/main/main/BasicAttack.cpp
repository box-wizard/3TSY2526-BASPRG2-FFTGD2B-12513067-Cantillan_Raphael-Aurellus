// BasicAttack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "BasicAttack.h"
#include "Unit.h"
#include <iostream>
#include <cstdlib>
using namespace std;

TheMOSTBasicHit::TheMOSTBasicHit() : Action("Basic Attack", 0)
{
}

void TheMOSTBasicHit::Execute(
    Unit* caster,
    vector<Unit*>& goodGuys,
    vector<Unit*>& badGuys)
{
    vector<Unit*> anyoneThere;
    for (Unit* badGuys : badGuys)
    {
        if (badGuys->IsAlive())
        {
            anyoneThere.push_back(badGuys);
        }
    }
    if (anyoneThere.empty())
    {
        return;
    }
    // ^ the piece above basically checks if there are any enemies that are still alive.
    // if there's none then it returns.
    int randomIndex = rand() % anyoneThere.size();
    Unit* target = anyoneThere[randomIndex];
    if (!WinRate(caster, target))
    {
        cout << caster->GetName()
            << "'s hit COMPLETELY MISSED!\n";
        return;
    }

    int damage = computeTotalDamage(caster, target, 1.0f);
    bool critical = false;
    if (rand() % 100 < 20)
    {
        damage = static_cast<int>(damage * 1.2f);
        critical = true;
    }
    // computes the total damage taken and rolls for the SECRET CRITICAL HIT!!
    target->GettingHit(damage);
    if (critical)
    {
        cout << "Oh wow, nice one! A CRITICAL HIT!\n";
    }
    cout << caster->GetName() << " winded up and prepared their Basic Attack on " << target->GetName() << "." << endl;
    cout << "The basic attack dealt " << damage << " damage!" << endl;
}
