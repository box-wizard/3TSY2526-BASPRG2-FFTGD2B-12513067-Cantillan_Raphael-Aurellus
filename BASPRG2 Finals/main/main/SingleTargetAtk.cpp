#include "SingleTargetAttack.h"
#include "Unit.h"
#include <iostream>
#include <cstdlib>
using namespace std;

SCREWYouInPARTICULAR::SCREWYouInPARTICULAR(string skillName) : Action(skillName, 5)
{

}
void SCREWYouInPARTICULAR::Execute(Unit* caster, vector<Unit*>& goodGuys,vector<Unit*>& badGuys)
{
    Unit* poorFool = nullptr;
    // finds the target, or rather, the POOR FOOL! thumbs up.
    for (Unit* badGuy : badGuys)
    {
        if (!badGuy->IsAlive())
        {
            continue;
        }

        if (poorFool == nullptr)
        {
            poorFool = badGuy;
        }
        else if (badGuy->GetHp() < poorFool->GetHp())
        {
            poorFool = badGuy;
        }
    }
    if (poorFool == nullptr)
    {
        return;
    }
    // if nobody's there, then it just goes back to what it was originally up to.
    caster->SpendingMP(GetMpCost());
    int OUCH = computeTotalDamage(caster, poorFool, 2.2f);
    poorFool->GettingHit(OUCH);
   // this piece basically makes you deduct MP
   // in addition, it also selects a target, the POOR FOOL, to be subjected to the damage. OUCH!!

    cout << caster->GetName() << " uses " << GetName()
        << " on " << poorFool->GetName() << "!\n";
    cout << poorFool->GetName() << " takes " << OUCH << " damage! - Yeowch!\n";
    cout << poorFool->GetName() << " Health Points: " << poorFool->GetHp()
        << "|" << poorFool->GetMaxHp() << "\n";
    cout << caster->GetName() << " Magic Points: " << caster->GetMp()
        << "|" << caster->GetMaxMp() << "\n";
    // this piece notifies the user about the battle going on right now
    // it shows the current health, magic points and the damage they took. the battle logs, if you will.
   
}


