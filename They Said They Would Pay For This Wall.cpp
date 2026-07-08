#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;
#include "Node.h" 

// incase i forget; this is basically adding the nodes.
void addMember(Node*& head, string name) {
    Node* newNode = new Node{ name, nullptr, nullptr };
    if (!head) 
    {
        head = newNode;
        head->next = head;
        head->previous = head;
    }
    else 
    {
        Node* tail = head->previous;
        tail->next = newNode;
        newNode->previous = tail;
        newNode->next = head;
        head->previous = newNode;
    }
}

int countMembers(Node* head) {
    if (!head) return 0;
    int count = 1;
    Node* temp = head;
    while (temp->next != head) { count++; temp = temp->next; }
    return count;
}

int main() {
    srand(time(0));
    Node* head = nullptr;
    int numSoldiers;

    cout << "Enter number of soldiers: ";
    cin >> numSoldiers;

    for (int i = 0; i < numSoldiers; i++) {
        string name;
        cout << "What's your name, soldier? ";
        cin >> name;
        addMember(head, name);
    }

    Node* current = head;
    int round = 1;

    while (countMembers(head) > 1) {
        cout << "\n================ ROUND " << round++ << " ================" << endl;
        cout << "Who's left:" << endl;
        Node* temp = head;
        do { cout << "  " << temp->name << endl; temp = temp->next; } while (temp != head);

        // the code block below prints the draw scenario and finds out
        int draw = (rand() % countMembers(head)) + 1;
        for (int i = 0; i < draw - 1; i++) current = current->next;

        cout << "\nResult: " << current->name << " drew " << draw << endl;

        Node* toDelete = current;
        current = toDelete->next;

        toDelete->previous->next = toDelete->next;
        toDelete->next->previous = toDelete->previous;
        if (toDelete == head) head = current;

        cout << toDelete->name << " was eliminated." << endl;
        delete toDelete;
    }

    cout << "\nThe only one remaining was " << head->name << " ...They went on to seek reinforcements." << endl;
    delete head;
    return 0;
}