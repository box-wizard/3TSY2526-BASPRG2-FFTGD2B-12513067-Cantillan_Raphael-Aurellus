#ifndef UNIT_H
#define UNIT_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

enum class UnitClass {
    Warrior,
    Assassin,
    Mage
};

inline string classToString(UnitClass unitClass) {
    switch (unitClass) {
    case UnitClass::Warrior: return "Warrior";
    case UnitClass::Assassin: return "Assassin";
    case UnitClass::Mage: return "Mage";
    }
    return "Unknown";
}

class Unit {
protected:
    string name;
    UnitClass unitClass;
    int Hitpoints;
    int MaximumHp;
    int MaxPower;
    int TheVitality;
    int TheirSpeed;
    int AbsolutePrecision;

public:
    Unit(string unitName, UnitClass unitClass, int unitHp, int unitPow, int unitVit, int unitAgi, int unitDex)
        : name(unitName), unitClass(unitClass), Hitpoints(unitHp), MaximumHp(unitHp), MaxPower(unitPow), TheVitality(unitVit), TheirSpeed(unitAgi), AbsolutePrecision(unitDex) {
    }

    virtual ~Unit() {}

    string getName() const { return name; }
    UnitClass getUnitClass() const { return unitClass; }
    int getHp() const { return Hitpoints; }
    int getMaxHp() const { return MaximumHp; }
    int getPower() const { return MaxPower; }
    int getVit() const { return TheVitality; }
    int getAgi() const { return TheirSpeed; }
    int getDex() const { return AbsolutePrecision; }

    bool isAlive() const { return Hitpoints > 0; }

    void heal(int amount) {
        Hitpoints = min(MaximumHp, Hitpoints + amount);
    }

    void addStats(int pBonus, int vBonus, int aBonus, int dBonus) {
        MaxPower += pBonus;
        TheVitality += vBonus;
        TheirSpeed += aBonus;
        AbsolutePrecision += dBonus;
        MaximumHp += (vBonus * 5);
        Hitpoints = min(MaximumHp, Hitpoints + (vBonus * 5));
    }

    double getDamageMultiplier(UnitClass defenderClass) const {
        if (unitClass == UnitClass::Warrior && defenderClass == UnitClass::Assassin) return 1.5;
        if (unitClass == UnitClass::Assassin && defenderClass == UnitClass::Mage) return 1.5;
        if (unitClass == UnitClass::Mage && defenderClass == UnitClass::Warrior) return 1.5;
        return 1.0;
    }

    int calculateDamage(const Unit& defender) const {
        double multiplier = getDamageMultiplier(defender.getUnitClass());
        int baseDamage = MaxPower - defender.getVit();
        if (baseDamage < 1) baseDamage = 1;
        return static_cast<int>(baseDamage * multiplier);
    }

    int calculateHitRate(const Unit& defender) const {
        double rate = (static_cast<double>(AbsolutePrecision) / defender.getAgi()) * 100.0;
        int hitRate = static_cast<int>(round(rate));
        return max(20, min(90, hitRate));
    }
    // OKAY so how this works is basically it converts your precision (dexterity stat basically.) and makes it a decimal
    // and then after that, it divides it by the opponent's agility stat and multiplies it by 100
    // then it converts it back to an integer. the return line basically makes it so that the final hit rate can't go below 20% or go beyond 80%

    bool attackAttempt(Unit& defender) {
        int hitChance = calculateHitRate(defender);
        int roll = rand() % 100;

        if (roll >= hitChance) {
            cout << name << " tries to attack " << defender.getName() << " but COMPLETELY MISSES! (Hit Rate: " << hitChance << "%)\n";
            return false;
        }

        int damage = calculateDamage(defender);
        defender.takeDamage(damage);
        cout << name << " whirls up an attack and completely hits " << defender.getName() << " for " << damage << " damage! (" << defender.getHp() << "/" << defender.getMaxHp() << " HP remaining)\n";
        return true;
    }

    void takeDamage(int damage) {
        Hitpoints = max(0, Hitpoints - damage);
    }

    void displayInfo() const {
        cout << "Name: " << name << " | Class: " << classToString(unitClass) << "\n";
        cout << "HP: " << Hitpoints << "/" << MaximumHp << " | POW: " << MaxPower << " | VIT: " << TheVitality << " | AGI: " << TheirSpeed << " | DEX: " << AbsolutePrecision << "\n";
    }
};

#endif