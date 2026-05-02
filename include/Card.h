#ifndef CARD_H
#define CARD_H

#include <string>

using namespace std;

// One card's basic info
// The real battle effect is handled in battle.cpp, otherwise this file gets too messy.
struct Card {
    string name;            // card name
    string description;     // card description
    string type;            // card type, such as Attack / Skill / Utility
    int cost;               // energy cost
    int value;              // main number of the card effect
    bool is_apply_to_enemy; // whether the card applies to enemy
    int times_played;       // combat counter used by scaling cards

    // Fallback card, mainly used when a name cannot be found.
    Card();

    // Create a card with full information
    Card(string name, string type, int cost, int value, string description, bool is_apply_to_enemy);

    // Read card information
    string getName() const;
    string getDescription() const;
    string getType() const;
    int getCost() const;
    int getValue() const;
    bool getIsApplyToEnemy() const;
    // Check whether current energy is enough
    bool isPlayable(int currentEnergy) const;

    // These functions are card templates.
    // If you want to add a new card, add another createXXX() function.
    static Card create_Strike();
    static Card create_Defend();
    static Card create_Heal();
    static Card create_Bash();
    static Card create_Recover();
    static Card create_Fireball();
    static Card create_Cleave();
    static Card create_QuickSlash();
    static Card create_IronWall();
    static Card create_Adrenaline();
    static Card create_Entrench();
    static Card create_Bloodletting();
    static Card create_PerfectedStrike();
    static Card create_Rampage();
};

#endif
