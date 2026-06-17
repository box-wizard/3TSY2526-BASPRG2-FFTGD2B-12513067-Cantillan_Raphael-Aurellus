// HEART OF THE CARDS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

const int CIVILIAN = 1;
const int EMPEROR = 2;
const int SLAVE = 3;
string cardname(int card) {
    if (card == CIVILIAN) return "Civilian";
    if (card == EMPEROR) return "Emperor";
    if (card == SLAVE) return "Slave";
    return "Huh?";
}
void playRound(int& round, int& mmLeft, int& moneyEarned) {
    bool kaijiE = false;
    if ((round >= 1 && round <= 3) || (round >= 7 && round <= 9)) {
        kaijiE = true;
    }
    cout << "\n\nROUND " << round << " - You are the " << (kaijiE ? "EMPEROR" : "SLAVE") << "!\n\n" << endl;
    cout << "Current Safety: " << mmLeft << "mm | Total Earnings: " << moneyEarned << " yen\n\n" << endl;
    // the function where you put your wager.
    int wager = 0;
    while (true) {
        cout << "Place your bet! (1 mm to " << mmLeft << " mm ): ";
        cin >> wager;
        if (wager >= 1 && wager <= mmLeft) {
            break;
        }
        cout << "\n\n\nThat's not possible within your current safety limit.\n\n";
    }

    vector<int> khand(4, CIVILIAN);
    vector<int> chand(4, CIVILIAN);

    if (kaijiE) {
        khand.push_back(EMPEROR);
        chand.push_back(SLAVE);
    }
    else {
        khand.push_back(SLAVE);
        chand.push_back(EMPEROR);
    }

    bool roundPass = false;
    bool kaijiWon = false;

    while (!roundPass && !khand.empty())
    {
        cout << "\n\nRemaining cards on hand: ";
        for (size_t i = 0; i < khand.size(); i++) {
            cout << "[" << i + 1 << ": " << cardname(khand[i]) << "] ";
        }
        cout << endl;

        int choice = 0;
        while (true) {
            cout << "Choose a card (1-" << khand.size() << "): ";
            cin >> choice;
            if (choice >= 1 && choice <= (int)khand.size()) {
                break;
            }
            cout << "[...You don't have a card in that number.]" << endl;
        }

        int kaijiCard = khand[choice - 1];
        int cindex = rand() % chand.size();
        int ccard = chand[cindex];

        cout << "\n-> Your card: " << cardname(kaijiCard) << endl;
        cout << "\n-> Enemy's card: " << cardname(ccard) << endl;

        khand.erase(khand.begin() + (choice - 1));
        chand.erase(chand.begin() + cindex);

        if (kaijiCard == CIVILIAN && ccard == CIVILIAN) {
            cout << "\n\nDRAW. Next card...\n\n" << endl;
        }
        else if (kaijiCard == EMPEROR && ccard == CIVILIAN) {
            cout << "\n\nYOU WIN!\n\n" << endl;
            kaijiWon = true;
            roundPass = true;
        }
        else if (kaijiCard == CIVILIAN && ccard == SLAVE) {
            cout << "\n\nYOU WIN!\n\n" << endl;
            kaijiWon = true;
            roundPass = true;
        }
        else if (kaijiCard == SLAVE && ccard == EMPEROR) {
            cout << "\n\nYOU WIN!\n\n" << endl;
            kaijiWon = true;
            roundPass = true;
        }
        else {
            cout << "\n\nYOU LOST...\n\n" << endl;
            kaijiWon = false;
            roundPass = true;
        }
    }

    if (kaijiWon) {
        int winnings = 0;
        if (kaijiE) {
            winnings = wager * 100000;
        }
        else {
            winnings = wager * 500000;
        }
        moneyEarned += winnings;
        cout << "\nYou earned " << winnings << " yen this round." << endl;
    }
    else {
        mmLeft -= wager;
        cout << "\nYou lost " << wager << " mm of safety." << endl;
    }
    round++;
}

int main()
{
    srand(time(0));

    int round = 1;
    int mmLeft = 30;
    int moneyEarned = 0;

    while (round <= 12 && mmLeft > 0)
    {
        playRound(round, mmLeft, moneyEarned);
    }
    cout << "\n=========================================" << endl;
    cout << "                GAME OVER                " << endl;
    cout << "=========================================" << endl;
    cout << "Final Safety Left: " << mmLeft << " mm" << endl;
    cout << "Total Earnings   : " << moneyEarned << " yen\n" << endl;

    // EVALUATING THE 3 DISTINCT ENDINGS
    if (mmLeft <= 0) {
        cout << "BAD ENDING: The device triggered! Your eardrum was pierced." << endl;
    }
    else if (moneyEarned >= 20000000) {
        cout << "GOOD ENDING: Freedom! You cleared your debts and walked away rich!" << endl;
    }
    else {
        cout << "NEUTRAL ENDING: You survived with your ear intact, but didn't hit the jackpot." << endl;
    }
    cout << "=========================================" << endl;

    return 0;
}