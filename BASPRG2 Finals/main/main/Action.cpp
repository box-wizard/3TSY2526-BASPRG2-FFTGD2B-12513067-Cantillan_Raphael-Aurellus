// Action.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Action.h"
#include "Unit.h"
#include <cstdlib>
#include <algorithm>

int Action::computeTotalDamage(Unit* attacker, Unit* target, float multiplier) const
{
    int Fortitude = attacker->GetPow();
    int variance = Fortitude * 20 / 100;
    int randFortitude = Fortitude + (rand() % (variance + 1));
    int baseOUCHIES = static_cast<int>(randFortitude * multiplier);
    int OUCHIES =
        baseOUCHIES - target->GetVit();
    // ^ this piece takes the damage, then multiples its damage at a 20% variance window
    // then it submits that damage on a range. for instance; a hit can deal at minimum 10 or at most 12.

    if (OUCHIES < 1)
    {
        OUCHIES = 1;
    }
    // ^ what this does is that if it only does *1* damage, then it *will* only do 1 damage.

    return OUCHIES;
}

bool Action::WinRate(Unit* attacker, Unit* defender) const
{
    int didTheyHit = attacker->GetDex() * 100 / defender->GetAgi();
    didTheyHit = max(55, min(didTheyHit, 95)); 
    // a clamp that makes it so that it has a minimum chance of 55% and a maximum chance of 95%
    int roll = rand() % 100 + 1;
    return roll <= didTheyHit;
}
Action::Action(string name, int mpCost)
    : initName(name), initMPCost(mpCost)
{
}
// this thing above basically takes a name and the cost of what you're doing and it looks at what it can do and whether
// the attack's possible or not
Action::~Action()
{
}
// ^ erases stuff
string Action::GetName() const
{
    return initName;
}
int Action::GetMpCost() const
{
    return initMPCost;
}
