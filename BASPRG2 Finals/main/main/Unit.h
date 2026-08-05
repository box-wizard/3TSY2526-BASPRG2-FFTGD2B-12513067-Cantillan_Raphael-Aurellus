#pragma once
#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <vector>

using namespace std;

class Action;

class Unit
{
private:
    string mName;

    int initHp;
    int initMaxHP;
    int initMp;
    int initMaxMP;

    int initPow;
    int initVit;
    int initAgi;
    int initDex;
// establishes the statistics; this will be used in the other files but the most important ones are "mMP", "mHP" and their Max counterparts as they track HP and MP

    bool mIsPlayer;
// this piece basically helps the code distinguish if the unit is on the player's side or the enemy's side

    vector<Action*> mActions;
// it COLLECTS MOVES (stores moves that the unit can use)

public:
    Unit(string name,
        int pow,
        int vit,
        int agi,
        int dex,
        int hp,
        int mp,
        bool isPlayer);

    ~Unit();
// what this does is to clean up stuff and erase unnecessary allocated memory
    void ExtraAction(Action* action);
    vector<Action*>& GetActions();

    void GettingHit(int damage);
    void outputHeal(int amount);

    bool SufficientMP(int cost) const;
    void SpendingMP(int cost);

    bool IsAlive() const;

    string GetName() const;

    int GetHp() const;
    int GetMaxHp() const;

    int GetMp() const;
    int GetMaxMp() const;

    int GetPow() const;
    int GetVit() const;
    int GetAgi() const;
    int GetDex() const;

    bool IsPlayer() const;
};

#endif