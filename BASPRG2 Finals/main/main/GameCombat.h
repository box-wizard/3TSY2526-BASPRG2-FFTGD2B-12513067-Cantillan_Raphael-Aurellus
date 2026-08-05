#pragma once
#ifndef GAMECOMBAT_H
#define GAMECOMBAT_H
#include "Team.h"
#include <string>
using namespace std;

class GameCombat
{
private:
    Team GoodGuys;
    Team BadGuys;

    vector<Unit*> initTurnOrder;
    int CurrentRotation = 0;

public:
    GameCombat();

    void Initialize();
    void Run();

private:
    void PlayerTurn(Unit* unit);
    void EnemyTurn(Unit* unit);
    void DisplayCurrentTeams() const;
    void DisplayCurrentRotation() const;
    void writeGoodGuys();
    void writeBadGuys();
    
    Unit* GetNextUnit();

    void CurrentTurnRotation();
    void RemoveDeadFromCycle();
    bool IsBattleOver() const;
};

#endif


