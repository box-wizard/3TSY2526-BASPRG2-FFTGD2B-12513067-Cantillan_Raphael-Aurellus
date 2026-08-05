#include "MultiTargetAttack.h"
#include "Unit.h"
#include "Action.h"
#include <iostream>
#include <cstdlib>
using namespace std;

KILLSALLOFYOU::KILLSALLOFYOU(string skillName) : Action(skillName, 4)
{

}

void KILLSALLOFYOU::Execute(Unit* caster, vector<Unit*>& allies,
    vector<Unit*>& enemies)
{
    bool isAnyoneThere = false;
    for (Unit* poorFool : enemies)
    {
        if (poorFool->IsAlive())
        {
            isAnyoneThere = true;
            break;
        }
    }
    if (!isAnyoneThere)
    {
        cout << "Only the cold wind whistles between you and the non-existent tension.\n";
        cout << "No enemies remain.\n";
        return;
    }
    // these pieces are here to check if there is an enemy left alive.
    // if nobody's there, then it just goes back to what it was originally up to.
    caster->SpendingMP(GetMpCost());
    cout << caster->GetName() << " uses " << GetName() << "!\n\n";
    // this piece basically makes you deduct MP
   // in addition, it also selects a target, the POOR FOOL, to be subjected to the damage. OUCH!!
    for (Unit* poorFool : enemies)
    {
        if (!poorFool->IsAlive())
        {
            continue;
        }
        int OUCH = computeTotalDamage(caster, poorFool, 0.9f);
        poorFool->GettingHit(OUCH);
        cout << poorFool->GetName() << " takes " << OUCH << " damage! - Woah!\n";

        cout << poorFool->GetName() << " Health Points: " << poorFool->GetHp()
            << "|" << poorFool->GetMaxHp() << "\n\n";
    }

    cout << caster->GetName() << " Magic Points: " << caster->GetMp()
        << "|" << caster->GetMaxMp() << endl;
    // deducts mana if there are enemies, and then prints out what goes on in the fight, similar to the SingularAtk file
    // or whatever i named it as.
}