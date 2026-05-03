#include "../include/Cardfactory.h"
#include <cstdlib>

namespace {
bool can_offer_aoe_card(int difficulty, int stage) {
    if(difficulty == 1) {
        return stage >= 6;
    }
    if(difficulty == 2) {
        return stage >= 5;
    }
    if(difficulty == 3) {
        return stage >= 3;
    }
    return false;
}

int aoe_offer_chance(int difficulty) {
    if(difficulty == 1) return 8;
    if(difficulty == 2) return 12;
    if(difficulty == 3) return 15;
    return 0;
}
}

// Put every rarity pool together. Mostly useful for debugging or future card lists.
vector<string> Cardfactory::getall_cardnames(){
    vector<string> names = get_common_cardnames();
    names.push_back("Cleave");
    vector<string> uncommon = get_uncommon_cardnames();
    vector<string> rare = get_rare_cardnames();

    names.insert(names.end(), uncommon.begin(), uncommon.end());
    names.insert(names.end(), rare.begin(), rare.end());
    return names;
}

// Cards that should appear often.
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

// Cards that should be less common than the basic pool.
vector<string> Cardfactory::get_uncommon_cardnames(){
    return {
        "Bloodletting",
        "Perfected Strike"
    };
}

// Rare cards are intentionally a tiny pool for now.
vector<string> Cardfactory::get_rare_cardnames(){
    return {
        "Entrench",
        "Rampage"
    };
}

// Turn a card name from save files or rewards into the actual Card object.
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
    if (card_name == "Cleave") {
        return Card::create_Cleave();
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

// Starter deck is small on purpose so the first few fights are easy to read.
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

// Weighted random card: common most of the time, rare only if the roll is lucky.
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

// Boss reward helper. It skips common/uncommon cards.
Card Cardfactory::create_random_rare_card(){
    vector<string> cardNames = get_rare_cardnames();
    int index = rand() % cardNames.size();
    return create_card(cardNames[index]);
}

// Reward choices are generated in a dynamic array first.
// After copying them into vector, we delete the array so there is no leak.
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

vector<Card> Cardfactory::create_reward_card(int count, int difficulty, int stage){
    vector<Card> rewards;
    if (count <= 0) {
        return rewards;
    }

    Card* reward_choices = new Card[count]; //using dynamic memory to create reward card
    for (int i = 0; i < count; i++) {
        if(can_offer_aoe_card(difficulty, stage) && rand() % 100 < aoe_offer_chance(difficulty)) {
            reward_choices[i] = create_card("Cleave");
        }
        else {
            reward_choices[i] = create_random_card();
        }
    }
    for (int i = 0; i < count; i++) {
        rewards.push_back(reward_choices[i]);
    }
    delete[] reward_choices;

    return rewards;
}



















