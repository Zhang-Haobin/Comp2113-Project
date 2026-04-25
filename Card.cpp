#include "Card.h"

using namespace std;

// Default card
Card::Card() {
    name = "Unknown";
    description = "No effect.";
    type = "Utility";
    cost = 0;
    value = 0;
}

// Create a custom card
Card::Card(string name, string type, int cost, int value, string description) {
    this->name = name;
    this->type = type;
    this->cost = cost;
    this->value = value;
    this->description = description;
}

// Get card name
string Card::getName() const {
    return name;
}

// Get card description
string Card::getDescription() const {
    return description;
}

// Get card type
string Card::getType() const {
    return type;
}

// Get card cost
int Card::getCost() const {
    return cost;
}

// Get card value
int Card::getValue() const {
    return value;
}

// Check whether current energy is enough to play the card
bool Card::isPlayable(int currentEnergy) const {
    return currentEnergy >= cost;
}


// Card database starts here
// To add a new card, copy one function and change its values
// Format:
// return Card("Name", "Type", cost, value, "Description");

// Basic attack card
Card Card::createStrike() {
    return Card("Strike", "Attack", 1, 6, "Deal 6 damage.");
}

// defend card
Card Card::createDefend() {
    return Card("Defend", "Skill", 1, 5, "Gain 5 block.");
}

// heal card
Card Card::createHeal() {
    return Card("Heal", "Utility", 1, 4, "Recover 4 HP.");
}
