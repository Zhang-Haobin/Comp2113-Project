#include "../include/Cardfactory.h"
#include <cstdlib>

vector<string> Cardfactory::getall_cardnames(){
    vector<string> names = get_common_cardnames();
    vector<string> uncommon = get_uncommon_cardnames();
    vector<string> rare = get_rare_cardnames();

    names.insert(names.end(), uncommon.begin(), uncommon.end());
    names.insert(names.end(), rare.begin(), rare.end());
    return names;
}

vector<string> Cardfactory::get_common_cardnames(){
    return {
        "Strike",
        "Defend",
        "Heal",
        "Bash",
        "Recover",
        "Fireball",
        "Quick Slash",
        "Iron Wall",
        "Adrenaline"
    };
}

vector<string> Cardfactory::get_uncommon_cardnames(){
    return {
        "Bloodletting",
        "Perfected Strike"
    };
}

vector<string> Cardfactory::get_rare_cardnames(){
    return {
        "Entrench",
        "Rampage"
    };
}

Card Cardfactory::create_card(const string& card_name) {
    if (card_name == "Strike") {
        return Card::create_Strike();
    }
    if (card_name == "Defend") {
        return Card::create_Defend();
    }
    if (card_name == "Heal") {
        return Card::create_Heal();
    }
    if (card_name == "Bash") {
        return Card::create_Bash();
    }
    if (card_name == "Recover") {
        return Card::create_Recover();
    }
    if (card_name == "Fireball") {
        return Card::create_Fireball();
    }
    if (card_name == "Quick Slash") {
        return Card::create_QuickSlash();
    }
    if (card_name == "Iron Wall") {
        return Card::create_IronWall();
    }
    if (card_name == "Adrenaline") {
        return Card::create_Adrenaline();
    }
    if (card_name == "Entrench") {
        return Card::create_Entrench();
    }
    if (card_name == "Bloodletting") {
        return Card::create_Bloodletting();
    }
    if (card_name == "Perfected Strike") {
        return Card::create_PerfectedStrike();
    }
    if (card_name == "Rampage") {
        return Card::create_Rampage();
    }

    return Card();
}

vector<Card> Cardfactory::create_starter_carddeck(){
    vector<Card> deck;
    for (int i=0;i<3;i++){
        deck.push_back(create_card("Strike"));
    }
    for (int i=0;i<2;i++){
        deck.push_back(create_card("Defend"));
    }
    deck.push_back(create_card("Heal"));
    return deck;
}

Card Cardfactory::create_random_card(){
    int roll = rand() % 100;
    vector<string> cardNames;

    if (roll < 60) {
        cardNames = get_common_cardnames();
    }
    else if (roll < 97) {
        cardNames = get_uncommon_cardnames();
    }
    else {
        cardNames = get_rare_cardnames();
    }

    int index = rand() % cardNames.size();

    return create_card(cardNames[index]);
}

Card Cardfactory::create_random_rare_card(){
    vector<string> cardNames = get_rare_cardnames();
    int index = rand() % cardNames.size();
    return create_card(cardNames[index]);
}

vector<Card> Cardfactory::create_reward_card(int count){
    vector<Card> rewards;
    if (count <= 0) {
        return rewards;
    }

       //copy the generated cards into the vector returned to the caller.
    Card* reward_choices = new Card[count];
    for (int i = 0; i < count; i++) {
        reward_choices[i] = create_random_card();
    }
    for (int i = 0; i < count; i++) {
        rewards.push_back(reward_choices[i]);
    }
    delete[] reward_choices;

    return rewards;
}






















