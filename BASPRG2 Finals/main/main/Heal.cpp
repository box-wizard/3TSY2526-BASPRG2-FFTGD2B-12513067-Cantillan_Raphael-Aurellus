// Heal.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Heal.h"
#include "Unit.h"
#include "Action.h"
#include <iostream>
#include <cstdlib>
using namespace std;
RestoresHEALTH::RestoresHEALTH(string skillName) : Action(skillName, 3)
{

}
void RestoresHEALTH::Execute(Unit* caster, vector<Unit*>& allies,
    vector<Unit*>& enemies)
{
    Unit* target = nullptr;
   
    for (Unit* ally : allies)
    {
        if (!ally->IsAlive())
        {
            continue;
        }
        if (ally->GetHp() == ally->GetMaxHp())
        {
            continue;
        }

        if (target == nullptr)
        {
            target = ally;
        }
        else if (ally->GetHp() < target->GetHp())
        {
            target = ally;
        }
    }
    if (target == nullptr)
    {
        cout << "All of your teammates look healthy!.\n";
        return;
    }
    caster->SpendingMP(GetMpCost());
    int variance = caster->GetPow() / 5;
    // deducts magic points and checks if there is actually a teammate that needs healing,
    // if there's none, then it cancels its action.
    if (variance < 1)
    {
        variance = 1;
    }
    int randomPow = caster->GetPow() + rand() % variance;
    int healAmount = static_cast<int>(randomPow * 1.5f);

    target->outputHeal(healAmount);
    cout << caster->GetName() << " uses " << GetName() << " on " << target->GetName() << "!\n";
    cout << target->GetName() << " heals them by " << healAmount << " Health Points! Make sure to say your thanks!\n";
    cout << target->GetName() << " Health Points: " << target->GetHp() << "|" << target->GetMaxHp() << "\n";
    cout << caster->GetName() << " Magic Points: " << caster->GetMp() << "|" << caster->GetMaxMp() << endl;
    // prints the healing battle logs; similar to the multi target and single 
}
