#ifndef CARDFACTORY_H
#define CARDFACTORY_H
#include "Card.h"
#include <vector>
#include <string>
using namespace std;
struct Cardfactory{
    //Create one card by its name.
    static Card create_card(const string& card_name);

//Create the player's starter deck.
    static vector<Card> create_starter_carddeck();

  // Create one random card with rarity weighting.
    
    static Card create_random_card();

    // Create one random rare card.
    
    static Card create_random_rare_card();

    // Create reward card choices using a temporary dynamic array.
    
    static vector<Card> create_reward_card(int count);

    //  Get all available card names.
    
    static vector<string> getall_cardnames();

    //  Get common card names.
   
    static vector<string> get_common_cardnames();

    // Get uncommon card names.
    
    static vector<string> get_uncommon_cardnames();

    //  Get rare card names.
  
    static vector<string> get_rare_cardnames();
};
#endif
