#include "Team.h"
#include "Unit.h"
Team::Team(string name)
{
    initName = name;
}
Team::~Team()
{
    for (Unit* member : TheCoolRoster)
    {
        delete member;
    }
    TheCoolRoster.clear();
}
// this piece deletes things, you already know the gist whenever there's a "~" on it
void Team::AddMember(Unit* member)
{
    TheCoolRoster.push_back(member);
}
// adds people in the team
vector<Unit*>& Team::GetMembers()
{
    return TheCoolRoster;
}
// gets how many people are in the team
const vector<Unit*>& Team::GetMembers() const
{
    return TheCoolRoster;
}

bool Team::GetDowned() const
{
    for (Unit* member : TheCoolRoster)
    {
        if (member->IsAlive())
        {
            return false;
        }
    }

    return true;
}

string Team::GetName() const
{
    return initName;
}
