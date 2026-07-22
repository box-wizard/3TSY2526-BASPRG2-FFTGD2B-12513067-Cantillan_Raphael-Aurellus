#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Unit.h"
#include "Warrior.h"
#include "Assassin.h"
#include "Mage.h"

using namespace std;

Unit* generateRandomOpponent(int floor) {
    int classRoll = rand() % 3;
    int scale = (floor - 1) * 2;

    string warriorNames[] = { "Julio Ceasar", "John A. Paul", "Don Quixote", "Lean Sigma" };
    string assassinNames[] = { "Assassin from Visionary Squad", "Assassin from Soul Knight", "Assassin from Fate/Grand Order", "Assassin from Vesteria" };
    string mageNames[] = { "Ursula Callistis", "Iguin", "Ivor Yefimovich", "Marisa Kirisame" };

    Unit* opponent = nullptr;

    if (classRoll == 0) {
        string oppName = warriorNames[rand() % 4];
        opponent = new Warrior(oppName);
        opponent->addStats(scale, scale, scale / 2, scale / 2);
    }
    else if (classRoll == 1) {
        string oppName = assassinNames[rand() % 4];
        opponent = new Assassin(oppName);
        opponent->addStats(scale + 1, scale / 2, scale, scale);
    }
    else {
        string oppName = mageNames[rand() % 4];
        opponent = new Mage(oppName);
        opponent->addStats(scale + 2, scale / 2, scale / 2, scale);
    }

    return opponent;
}

void THESPOILSOFWAR(Unit* player, UnitClass defeatedClass) {
    if (defeatedClass == UnitClass::Warrior) {
        cout << "You've thoroughly torn your opponent asunder! Gained +3 POWER and +3 VIT. -- You move forth to the next scene...\n";
        player->addStats(3, 3, 0, 0);
    }
    else if (defeatedClass == UnitClass::Assassin) {
        cout << "You've ripped your opponent a new one! Gained +3 AGI and +3 DEX. -- You move forth to the next scene...\n";
        player->addStats(0, 0, 3, 3);
    }
    else if (defeatedClass == UnitClass::Mage) {
        cout << "You've successfully vanquished the enemy! You gained +5 POWER. -- You move forth to the next scene...\n";
        player->addStats(5, 0, 0, 0);
    }

    int healAmount = static_cast<int>(player->getMaxHp() * 0.50);
    player->heal(healAmount);
    cout << "As you exit the scene, you feel a serene wave washing over you.. (+" << healAmount << " HP).\n";
}

bool theActualBattle(Unit* player, Unit* opponent) {
    cout << "BATTLE START! The tension surges as you face your opponent!\n\n\n";

    player->displayInfo();
    cout << "\n\n---VERSUS---\n\n";
    opponent->displayInfo();

    system("pause");
    system("cls");

    int turnCount = 1;
    while (player->isAlive() && opponent->isAlive()) {
        cout << "Scene " << turnCount << "\n\n\n";

        if (player->getAgi() >= opponent->getAgi()) {
            player->attackAttempt(*opponent);
            if (opponent->isAlive()) {
                opponent->attackAttempt(*player);
            }
        }
        else {
            opponent->attackAttempt(*player);
            if (player->isAlive()) {
                player->attackAttempt(*opponent);
            }
        }

        turnCount++;
        cout << "\n";

        system("pause");
        system("cls");
    }

    return player->isAlive();
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    cout << "WELCOME TO THE GAUNTLET!\n\n\n";

    cout << "Choose your character:\n";
    cout << "[1] Warrior\n";
    cout << "[2] Assassin\n";
    cout << "[3] Mage\n";
    cout << "Select class (1-3): ";

    int classChoice = 0;
    cin >> classChoice;
    system("cls");

    while (classChoice < 1 || classChoice > 3) {
        cout << "Invalid input. Please choose an option between 1 and 3: ";
        cin >> classChoice;
    }

    cin.ignore();
    cout << "Enter your hero's name: ";
    string playerName;
    getline(cin, playerName);

    Unit* player = nullptr;
    if (classChoice == 1) {
        player = new Warrior(playerName);
    }
    else if (classChoice == 2) {
        player = new Assassin(playerName);
    }
    else {
        player = new Mage(playerName);
    }

    cout << "\n\nYour adventure begins.\n\n";
    player->displayInfo();
    cout << "\n\n";

    system("pause");
    system("cls");

    int floor = 1;
    bool playerIsVictorious = true;

    while (playerIsVictorious) {
        cout << "\n\n\nARENA FLOOR " << floor << "\n\n\n";

        Unit* opponent = generateRandomOpponent(floor);
        playerIsVictorious = theActualBattle(player, opponent);

        if (playerIsVictorious) {
            cout << "You have THOROUGHLY VANQUISHED " << opponent->getName() << "!\n";
            THESPOILSOFWAR(player, opponent->getUnitClass());
            delete opponent;
            floor++;
            cout << "\n--- Your Current Status ---\n";
            player->displayInfo();

            system("pause");
            system("cls");
        }
        else {
            cout << "You have been swept away on Floor " << floor << " by " << opponent->getName() << "...\n";
            delete opponent;
        }
    }

    cout << "GAME OVER.\n\n\n";
    cout << "Final progress: Cleared " << (floor - 1) << " floors!\n\n\n";
    cout << "Thank you for playing!\n";

    delete player;
    return 0;
}