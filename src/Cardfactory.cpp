#include "../include/Cardfactory.h"
#include <cstdlib>

vector<string> Cardfactory::getall_cardnames(){
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
    vector<string> cardNames = getall_cardnames();

    int index = rand() % cardNames.size();

    return create_card(cardNames[index]);
}


vector<Card> Cardfactory::create_reward_card(int count){
    vector<Card> rewards;
    for (int i = 0; i < count; i++) {
        rewards.push_back(create_random_card());
    }
    return rewards;
}
























