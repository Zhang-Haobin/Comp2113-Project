#ifndef CARDFACTORY_H
#define CARDFACTORY_H
#include "Card.h"
#include <vector>
#include <string>
using namespace std;

// This is basically the card shop / card database.
// Other files ask it for cards instead of manually typing card stats everywhere.
struct Cardfactory{
    // Find a card template by name and return a fresh copy of it.
    static Card create_card(const string& card_name);

    // Create the stater deck 
    static vector<Card> create_starter_carddeck();

    // Random reward card. 
    static Card create_random_card();

    // Bosses can use this so the reward feels a bit better.
    static Card create_random_rare_card();

    // Make several reward choices. This also shows our dynamic memory part.
    static vector<Card> create_reward_card(int count);

    // Make reward choices with difficulty/stage-aware cards.
    static vector<Card> create_reward_card(int count, int difficulty, int stage);

    static vector<string> getall_cardnames();

    // Common cards are the usual reward pool.
    static vector<string> get_common_cardnames();


    static vector<string> get_uncommon_cardnames();

    // The rare pool, mostly for lucky rolls and boss rewards.
    static vector<string> get_rare_cardnames();
};
#endif
