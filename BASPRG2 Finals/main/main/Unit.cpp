#include "Unit.h"
#include "Action.h"
#include <iostream>
using namespace std;

Unit::Unit(string name,
    int pow,
    int vit,
    int agi,
    int dex,
    int hp,
    int mp,
    bool isPlayer)
{
    mName = name;

    initHp = hp;
    initMaxHP = hp;

    initMp = mp;
    initMaxMP = mp;

    initPow = pow;
    initVit = vit;
    initAgi = agi;
    initDex = dex;

    mIsPlayer = isPlayer;
}

void Unit::GettingHit(int damage)
{
    initHp -= damage;

    if (initHp < 0)
    {
        initHp = 0;
    }
}
// taking damage. what this does is subtract health from how much damage the attack did
// basic arithmetic things
Unit::~Unit()
{
    for (Action* action : mActions)
    {
        delete action;
    }
    mActions.clear();
}
// basically what this does is whenever a 'unit' object is destroyed; it cleans it up to save memory-
// in game terms: when a unit dies, their current memory gets erased. once the memory's gone, it also deletes the actions of that unit
void Unit::outputHeal(int amount)
{
    initHp += amount;
    if (initHp > initMaxHP)
    {
        initHp = initMaxHP;
    }
}
// healing. gives a unit health if a unit get healed
void Unit::ExtraAction(Action* action)
{
    mActions.push_back(action);
}

vector<Action*>& Unit::GetActions()
{
    return mActions;
}
bool Unit::SufficientMP(int cost) const
{
    return initMp >= cost;
}
void Unit::SpendingMP(int cost)
{
    initMp -= cost;

    if (initMp < 0)
    {
        initMp = 0;
    }
}

bool Unit::IsAlive() const
{
    return initHp > 0;
}

string Unit::GetName() const
{
    return mName;
}

int Unit::GetHp() const
{
    return initHp;
}

int Unit::GetPow() const
{
    return initPow;
}

int Unit::GetMaxHp() const
{
    return initMaxHP;
}

int Unit::GetMp() const
{
    return initMp;
}

int Unit::GetMaxMp() const
{
    return initMaxMP;
}

int Unit::GetVit() const
{
    return initVit;
}

int Unit::GetAgi() const
{
    return initAgi;
}

int Unit::GetDex() const
{
    return initDex;
}

bool Unit::IsPlayer() const
{
    return mIsPlayer;
}