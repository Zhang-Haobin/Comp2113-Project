#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>

#include "Card.h"

using namespace std;

// only defines the player states and actions
// does NOT do the battle logic

class Player {
public:
    string name;
    int max_hp = 60;
    int hp = 60;
    int max_energy = 3;
    int energy = 3;
    int strength = 1;                // damage multiplier
    int damage_boost = 0;            // damage boost
    int armor = 0;                   // damage reduction
    int stage = 0;                   // current stage
    int difficulty = 2;              // difficulty
    int max_card = 6;                // max number of cards held at the same time
    vector<Card> cards = {};

    // these functions ONLY RETURNS a value:

    int get_hp_after_heal(int hp_add);
    int get_hp_after_hurt(int hp_minus);
    int get_damage(int atk);
};

#endif
