#pragma once
#ifndef TEAM_H
#define TEAM_H

#include <string>
#include <vector>

using namespace std;

class Unit;
class Team
{
private:
    string initName;
    vector<Unit*> TheCoolRoster;

public:
    Team(string name = "");
    ~Team();

    void AddMember(Unit* unit);

    vector<Unit*>& GetMembers();
    const vector<Unit*>& GetMembers() const;

    bool GetDowned() const;
    string GetName() const;
};
#endif

