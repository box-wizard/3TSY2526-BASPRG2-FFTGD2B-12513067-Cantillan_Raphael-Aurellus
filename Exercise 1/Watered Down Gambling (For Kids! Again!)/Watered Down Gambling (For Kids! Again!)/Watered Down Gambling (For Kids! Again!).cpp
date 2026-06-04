// Watered Down Gambling (For Kids! Again!).cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>

using namespace std;
int thebet(int& money) {
    int wager;
    while (true) {
        cout << "You currently have " << money << " gold. How much are you willing to cough up? [Must be more than: 0]\n\n";
        cin >> wager;

        if (wager > 0 && wager <= money) {
            money -= wager;
            return wager;
        }
        cout << "\nMan, what a brilliant idea- How about betting nothing? Try again.\n\n";
    }
}

void thebetvoid(int& money, int& mref) {
    while (true) {
        cout << "You currently have " << money << " gold. How much are you willing to cough up? [Must be more than: 0]\n\n";
        cin >> mref;

        if (mref > 0 && mref <= money) {
            money -= mref;
            return;
        }
        cout << "\n\nMan, what a brilliant idea- How about betting nothing? Try again.\n\n";
    }
}

void roll(int& die1, int& die2) {
    die1 = (rand() % 6) + 1;
    die2 = (rand() % 6) + 1;
}

void pay(int& money, int wager, int pdie1, int pdie2, int cdie1, int cdie2) {

    int playersum = pdie1 + pdie2;
    int oppsum = cdie1 + cdie2;

    cout << "\n\n [!] THE OUTCOME [!]\n\n" << endl;
    cout << "Your opponent has rolled: " << cdie1 << " + " << cdie2 << " = " << oppsum << endl;
    cout << "You have rolled: " << pdie1 << " + " << pdie2 << " = " << playersum << endl;

    bool playersnake = (pdie1 == 1 && pdie2 == 1);
    bool csnake = (cdie1 == 1 && cdie2 == 1);

    if (playersum == oppsum) {
        cout << "\n\nAh.. A draw.\n\n" << endl;
        money += wager;
    }
    else if (playersnake) {
        cout << "\nAmidst your luck, you rolled SNAKE EYES! " << wager * 3 << " gold...!\n\n" << endl;
        money += (wager * 3);
    }
    else if (playersum > oppsum) {
        cout << "\nYOU WIN. You get " << wager * 2 << " gold.\n\n" << endl;
        money += (wager * 2);
    }
    else {
        cout << "\nA loss. Not the first time, and certainly not the last.\n\n" << endl;
    }
}

void rund(int& gold) {
    int bet = thebet(gold);
    int cdie1 = 0, cdie2 = 0;
    int pdie1 = 0, pdie2 = 0;
    roll(cdie1, cdie2);
    roll(pdie1, pdie2);
    pay(gold, bet, pdie1, pdie2, cdie1, cdie2);
}

int main() {
    srand(time(NULL));

    int gold = 1000;
    cout << "Let's play dice, shall we?" << endl;

    while (gold > 0) {
        rund(gold);
    }

    cout << "GAME OVER. No matter how avaricious you become, It is as they always say... The House always wins." << endl;
    return 0;
}
