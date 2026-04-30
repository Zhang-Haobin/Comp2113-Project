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
    int block = 0;                   // damage reduction
    int stage = 0;                   // current stage
    int difficulty = 2;              // difficulty
    int max_card = 6;                // max number of cards held at the same time
    vector<Card> cards = {};

    int get_damage(int atk) const;
    
    void heal(const int delta);
    void hurt(const int delta);
};

#endif // ifndef PLAYER_H
