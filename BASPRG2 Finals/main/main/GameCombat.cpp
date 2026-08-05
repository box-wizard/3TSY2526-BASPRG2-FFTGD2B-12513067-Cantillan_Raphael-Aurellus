#include "GameCombat.h"
#include "Unit.h"
#include "BasicAttack.h"
#include "SingleTargetAttack.h"
#include "MultiTargetAttack.h"
#include "Heal.h"
#include "Action.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

GameCombat::GameCombat()
    : GoodGuys("Sinners"), BadGuys("Enemies")
{
}

void GameCombat::Initialize()
{
    writeGoodGuys();
    writeBadGuys();
    CurrentTurnRotation();
}

bool GameCombat::IsBattleOver() const
{
    return GoodGuys.GetDowned() || BadGuys.GetDowned();
}

Unit* GameCombat::GetNextUnit()
{
    if (initTurnOrder.empty())
        return nullptr;

    if (CurrentRotation >= static_cast<int>(initTurnOrder.size()))
        CurrentRotation = 0;

    Unit* current = initTurnOrder[CurrentRotation];
    CurrentRotation++;

    if (CurrentRotation >= static_cast<int>(initTurnOrder.size()))
        CurrentRotation = 0;

    return current;
}

void GameCombat::RemoveDeadFromCycle()
{
    for (int i = 0; i < static_cast<int>(initTurnOrder.size());)
    {
        if (!initTurnOrder[i]->IsAlive())
        {
            if (i < CurrentRotation)
            {
                CurrentRotation--;
            }
            initTurnOrder.erase(initTurnOrder.begin() + i);
        }
        else
        {
            i++;
        }
    }

    if (CurrentRotation < 0)
        CurrentRotation = 0;

    if (CurrentRotation >= static_cast<int>(initTurnOrder.size()))
        CurrentRotation = 0;
}

void GameCombat::CurrentTurnRotation()
{
    initTurnOrder.clear();

    for (Unit* unit : GoodGuys.GetMembers())
        initTurnOrder.push_back(unit);

    for (Unit* unit : BadGuys.GetMembers())
        initTurnOrder.push_back(unit);

    sort(initTurnOrder.begin(), initTurnOrder.end(), [](Unit* a, Unit* b) {
        return a->GetAgi() > b->GetAgi();
        });

    CurrentRotation = 0;
}

void GameCombat::DisplayCurrentRotation() const
{
    cout << "[:>:(=============]> CYCLE ORDER <[=============):<:]" << endl;

    for (size_t i = 0; i < initTurnOrder.size(); ++i)
    {
        cout << i + 1 << ". ";
        string teamLabel = initTurnOrder[i]->IsPlayer() ? GoodGuys.GetName() : BadGuys.GetName();
        cout << "[" << teamLabel << "] "
            << initTurnOrder[i]->GetName()
            << " - " << initTurnOrder[i]->GetAgi() << " AGI";

        if (!initTurnOrder[i]->IsAlive())
        {
            cout << " [DEAD]";
        }
        cout << endl;
    }

    cout << "[:>:(=============]> CYCLE ORDER <[=============):<:]" << endl;
}

void GameCombat::DisplayCurrentTeams() const
{
    auto printTeam = [](const string& teamName, const vector<Unit*>& members, bool fancyHeader) {
        if (fancyHeader) {
            cout << "[:>:(==========================================):<]" << endl;
        }
        else {
            cout << "[:>:(==========================================):<]" << endl;
        }
        cout << "Team: " << teamName << endl;
        if (fancyHeader) {
            cout << "[:>:(==========================================):<]" << endl;
        }
        else {
            cout << "[:>:(==========================================):<]" << endl;
        }

        for (Unit* unit : members)
        {
            cout << unit->GetName();
            if (unit->IsAlive())
            {
                cout << " [HP: " << unit->GetHp() << "/" << unit->GetMaxHp() << "]";
            }
            else
            {
                cout << " [DEAD]";
            }
            cout << endl;
        }
        cout << endl;
        };

    printTeam(GoodGuys.GetName(), GoodGuys.GetMembers(), true);
    printTeam(BadGuys.GetName(), BadGuys.GetMembers(), false);
}

void GameCombat::PlayerTurn(Unit* unit)
{
    vector<Action*>& actions = unit->GetActions();
    int choice = -1;

    while (true)
    {
        system("pause");
        system("cls");
        cout << "[STATS] [==============================]" << endl;
        cout << "Name: " << unit->GetName() << endl;
        cout << "HP: " << unit->GetHp() << "|" << unit->GetMaxHp() << endl;
        cout << "MP: " << unit->GetMp() << "|" << unit->GetMaxMp() << endl;
        cout << "POW: " << unit->GetPow() << endl;
        cout << "VIT: " << unit->GetVit() << endl;
        cout << "DEX: " << unit->GetDex() << endl;
        cout << "AGI: " << unit->GetAgi() << endl << endl;
        cout << "[======================================]" << endl;

        for (size_t i = 0; i < actions.size(); ++i)
        {
            cout << i + 1 << ". " << actions[i]->GetName()
                << " (MP Cost: " << actions[i]->GetMpCost() << ")\n";
        }

        cout << "\nMake your move: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (choice < 1 || choice > static_cast<int>(actions.size()))
        {
            cout << "Invalid choice.\n";
            continue;
        }

        system("cls");
        Action* selectedAction = actions[choice - 1];

        if (!unit->SufficientMP(selectedAction->GetMpCost()))
        {
            cout << "Not enough MP!\n";
            continue;
        }

        selectedAction->Execute(unit, GoodGuys.GetMembers(), BadGuys.GetMembers());
        break;
    }
}

void GameCombat::EnemyTurn(Unit* unit)
{
    system("pause");
    system("cls");
    cout << "\nEnemy Turn...\n" << endl;

    vector<Action*>& actions = unit->GetActions();
    Action* selectedAction = actions[0];

    if (actions.size() > 1)
    {
        Action* skill = actions[1];
        if (unit->SufficientMP(skill->GetMpCost()) && (rand() % 2 == 0))
        {
            selectedAction = skill;
        }
    }

    selectedAction->Execute(unit, BadGuys.GetMembers(), GoodGuys.GetMembers());
}

void GameCombat::writeGoodGuys()
{
    // Order: POW, VIT, AGI, DEX, HP, MP, incase i forget.
    // i've forgotten a few times so uhhh
    Unit* myCompass = new Unit("Ishmael", 28, 30, 32, 15, 239, 20, true);
    myCompass->ExtraAction(new TheMOSTBasicHit());
    myCompass->ExtraAction(new KILLSALLOFYOU("Deadly Obsession"));
    GoodGuys.AddMember(myCompass);

    Unit* WildHuntHeathcliff = new Unit("Heathcliff", 33, 25, 32, 33, 276, 25, true);
    WildHuntHeathcliff->ExtraAction(new TheMOSTBasicHit());
    WildHuntHeathcliff->ExtraAction(new SCREWYouInPARTICULAR("Upheaval"));
    GoodGuys.AddMember(WildHuntHeathcliff);

    Unit* JadeEyes = new Unit("Hong Lu", 27, 27, 32, 14, 203, 60, true);
    JadeEyes->ExtraAction(new TheMOSTBasicHit());
    JadeEyes->ExtraAction(new RestoresHEALTH("Frivolous Jokes"));
    GoodGuys.AddMember(JadeEyes);
    // the heroes; instead of it being based off of WoW or LoL, they're based off of Limbus Company.
    // just like the piece below, this sets up their special attack, stats, etc.
}

void GameCombat::writeBadGuys()
{
    Unit* gasLighter = new Unit("Captain Ahab", 32, 12, 30, 18, 330, 17, false);
    gasLighter->ExtraAction(new TheMOSTBasicHit());
    gasLighter->ExtraAction(new SCREWYouInPARTICULAR("Weight of Guilt"));
    BadGuys.AddMember(gasLighter);

    Unit* contempt = new Unit("Jia Huan", 35, 15, 30, 10, 456, 20, false);
    contempt->ExtraAction(new TheMOSTBasicHit());
    contempt->ExtraAction(new KILLSALLOFYOU("Spiraling Gaze of Contempt"));
    BadGuys.AddMember(contempt);

    Unit* fellBullet = new Unit("Gubo", 29, 10, 30, 14, 326, 30, false);
    fellBullet->ExtraAction(new TheMOSTBasicHit());
    fellBullet->ExtraAction(new RestoresHEALTH("Heart Toward the New Era"));
    BadGuys.AddMember(fellBullet);
    // the enemies; instead of it being based off of WoW or LoL, they're based off of Limbus Company.
    // just like the piece above, this sets up their special attack, stats, etc.
}

void GameCombat::Run()
{
    while (!IsBattleOver())
    {
        system("cls");
        DisplayCurrentTeams();
        DisplayCurrentRotation();

        Unit* currentUnit = GetNextUnit();
        if (currentUnit == nullptr)
            break;

        cout << endl << "[SCENARIO]: ";
        string activeTeamName = currentUnit->IsPlayer() ? GoodGuys.GetName() : BadGuys.GetName();
        cout << "~[" << activeTeamName << "]~ " << currentUnit->GetName() << "\n\n";

        if (currentUnit->IsPlayer())
        {
            PlayerTurn(currentUnit);
        }
        else
        {
            EnemyTurn(currentUnit);
        }

        RemoveDeadFromCycle();
        cout << endl;
        system("pause");
    }

    system("cls");
    DisplayCurrentTeams();

    if (!GoodGuys.GetDowned())
    {
        cout << "\The Winner is declared: " << GoodGuys.GetName() << "!\n";
    }
}