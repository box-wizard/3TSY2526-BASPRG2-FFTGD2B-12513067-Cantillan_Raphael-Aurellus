#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>   

using namespace std;
vector<string> fillInventory(const vector<string>& itemPool);
void displayInventory(const vector<string>& inventory);
int countItem(const vector<string>& inventory, const string& counting);
void removeItem(vector<string>& inventory, const string& banish);

int main() {
    // code below basically allows that not every run will be the same
    srand(static_cast<unsigned int>(time(0)));

    // pool of items that can appear
    vector<string> availableItems = { "Iron Ingot", "Elixir", "Empty Bottle", "Blue Potion", "Red Potion", "Golden Nugget", "Teto", "Crystal Shard" };

    cout << "================================================================================\n";
    cout << "You suddenly come to a stop and decide to check your inventory...\nBecause, you know, you started to feel like you're a lot more slower\nthan usual with your bag as your items click against each other." << endl;
    cout << "================================================================================\n";

    // generates the pool by passing down the list above
    vector<string> myInventory = fillInventory(availableItems);

    cout << "\n\n\n================================================================================\n";
    cout << "You settled down in a quiet part of the woods. Putting down your bulky \nleather bag into the soft tuft of grass as you settled down, you took \noff the iron buckle of your bag and saw what you had. Though your bag \nwas, admittedly, a little rough to look at from the inside but you decided \nto do an inventory check anyway." << endl;
    cout << "================================================================================\n";
    displayInventory(myInventory);

    cout << "================================================================================\n";
    system("pause");
    system("cls");
    cout << "================================================================================\n";
    // selects a completely random item and counts it.
    int randomChoiceIndex = rand() % availableItems.size();
    string counting = availableItems[randomChoiceIndex];

    int itemRandomCount = countItem(myInventory, counting);
    if (itemRandomCount == 0) {
        cout << "You suddenly start to ask if you have enough " << counting << "s... \nAs you pull your hand up from out of your bag, you keep rummaging further and further...\nYour heart sinks as you realize you have exactly 0 " << counting << "s..!" << endl;
    }
    else {
        cout << "You suddenly start to ask if you have enough " << counting << "s, \nyou start rummaging through your bag and found exactly ";
        cout << itemRandomCount << " " << counting;
        if (itemRandomCount == 1) {
            cout << "." << endl;
        }
        else {
            cout << "s." << endl;
        }
    }
    cout << "================================================================================\n";
    system("pause");
    system("cls");
    cout << "================================================================================\n";
    // this would pick a random item to suddenly vanish from your inventory.
    int randomBanishIndex = rand() % availableItems.size();
    string banish = availableItems[randomBanishIndex];

    cout << "A sudden clumsy moment hits you, a loose root holds onto your foot as you fell\n";
    cout << "forward! As you fell, you accidentally drop and lose all instances of '" << banish << "'!" << endl;
    removeItem(myInventory, banish);

    cout << "\nYou reluctantly look at your bag, hoping and praying that you did not just\n";
    cout << "lose everything you just got, and thankfully, you didn't. Instead you only have:\n";
    displayInventory(myInventory);
    cout << "================================================================================\n";

    return 0;
}

// function definitions

// adds randomly generated bullshit into your inventory
vector<string> fillInventory(const vector<string>& itemPool) {
    vector<string> inventory;

    for (int i = 0; i < 10; ++i) {
        int randomIndex = rand() % itemPool.size();
        inventory.push_back(itemPool[randomIndex]);
    }

    return inventory;
}

// displays your inventory
void displayInventory(const vector<string>& inventory) {
    if (inventory.empty()) {
        cout << "wait why is your inventory empty" << endl;
        return;
    }

    for (int i = 0; i < inventory.size(); ++i) {
        cout << i + 1 << ". " << inventory[i] << endl;
    }
}

// counts an item
int countItem(const vector<string>& inventory, const string& counting) {
    int count = 0;
    for (int i = 0; i < inventory.size(); ++i) {
        if (inventory[i] == counting) {
            count++;
        }
    }
    return count;
}

// removes an item
void removeItem(vector<string>& inventory, const string& banish) {
    for (int i = inventory.size() - 1; i >= 0; --i) {
        if (inventory[i] == banish) {
            inventory.erase(inventory.begin() + i);
        }
    }
}