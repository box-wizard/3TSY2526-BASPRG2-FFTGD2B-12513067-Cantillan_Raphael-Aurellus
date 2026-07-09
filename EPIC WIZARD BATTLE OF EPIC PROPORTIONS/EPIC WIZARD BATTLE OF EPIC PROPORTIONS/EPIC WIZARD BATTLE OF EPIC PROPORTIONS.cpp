// EPIC WIZARD BATTLE OF EPIC PROPORTIONS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Wiz;

class Spell
{
public:
    string name;
    int mindmg;
    int maxdmg;
    int mpCost;

    Spell(string n, int min, int max, int cost)
    {
        name = n;
        mindmg = min;
        maxdmg = max;
        mpCost = cost;
    }

    void activ(Wiz* caster, Wiz* target);
};

class Wiz
{
public:
    string name;
    int hp;
    int mp;
    int mindmg;
    int maxdmg;

    Spell* spell;

    Wiz(string n)
    {
        name = n;
        hp = 250;
        mp = 0;

        mindmg = 10;
        maxdmg = 15;

        spell = new Spell("\n\nFireball", 40, 60, 50);

        cout << name << " enters battle!\n" << endl;
    }

    void atk(Wiz* target)
    {
        int dmg = rand() % (maxdmg - mindmg + 1) + mindmg;
        int gain = rand() % 11 + 10;

        target->hp -= dmg;
        mp += gain;

        cout << endl;
        cout << name << " attacks " << target->name << "!" << endl;
        cout << "\n\nDamage dealt: " << dmg << endl;
        cout << name << " gains " << gain << " Magic Points!" << endl;

        if (target->hp < 0)
            target->hp = 0;

        cout << target->name << "'s HP: " << target->hp << endl;
        cout << name << "'s MP: " << mp << endl;
    }

    bool dead()
    {
        return hp <= 0;
    }

    ~Wiz()
    {
        delete spell;
        cout << name << " has retreated back to their spot.\n" << endl;
    }
};

void Spell::activ(Wiz* caster, Wiz* target)
{
    if (caster->mp < mpCost)
    {
        cout << caster->name << " tried to cast " << name << " but doesn't have enough MP!\n\n" << endl;
        return;
    }

    caster->mp -= mpCost;

    int dmg = rand() % (maxdmg - mindmg + 1) + mindmg;

    target->hp -= dmg;

    if (target->hp < 0)
        target->hp = 0;

    cout << endl;
    cout << caster->name << " casts " << name << "!\n\n" << endl;
    cout << "\n\nSpell damage: " << dmg << endl;
    cout << caster->name << "'s MP: " << caster->mp << "\n" << endl;
    cout << target->name << "'s HP: " << target->hp << "\n" << endl;
}

int main()
{
    srand(time(NULL));

    Wiz* wiz1 = new Wiz("Merlin");
    Wiz* wiz2 = new Wiz("Morgana");
    cout << "==============[!] BATTLE START! The tension surges as the announcer shouts from the podium; FIGHT! [!]==============\n\n";
    cout << "\t\tBoth combatants draw their staves and brace for the fight ahead. With " << wiz1->name << " and " << wiz2->name;
    cout << "\n\tabout to throw down for the entertainment of the crowd! The crowd cheers on as they're about to attack!\n\n";
    cout << "====================================================================================================================\n\n";

    while (!wiz1->dead() && !wiz2->dead())
    {
        if (wiz1->mp >= wiz1->spell->mpCost)
        {
            wiz1->spell->activ(wiz1, wiz2);
        }
        else
        {
            wiz1->atk(wiz2);
        }

        if (wiz2->dead())
            break;

        if (wiz2->mp >= wiz2->spell->mpCost)
        {
            wiz2->spell->activ(wiz2, wiz1);
        }
        else
        {
            wiz2->atk(wiz1);
        }

        if (wiz1->dead())
            break;
    }

    cout << "\n============================[ ! ] The trumpets blare! -- The round has concluded! [ ! ]============================\n";
    cout << "\n\t\t\tThe announcer has advised both combatants to retreat and be \n\t\t\t\t\ttreated for the next round!\n\n";
    cout << "====================================================================================================================\n";

    if (wiz1->dead())
    {
        cout << wiz2->name << " wins!\n" << endl;
    }
    else
    {
        cout << wiz1->name << " wins!\n" << endl;
    }

    delete wiz1;
    delete wiz2;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
