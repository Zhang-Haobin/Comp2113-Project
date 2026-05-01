#ifndef CARDFACTORY_H
#define CARDFACTORY_H
#include "Card.h"
#include <vector>
#include <string>
using namespace std;
//Create cards by name
//create initial decks
//randomly generate reward cards
struct Cardfactory{
    static Card create_card(const string& card_name);
    static vector<Card> create_starter_carddeck();    //create the starter deck
    static Card create_random_card();
    static vector<Card> create_reward_card(int count);
    static vector<string> getall_cardnames();
};
#endif