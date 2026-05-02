#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>

#include "../include/battle.h"
#include "../include/main.h"
#include "../include/save.h"
#include "../include/Cardfactory.h"
#include "../include/Deck.h"

using namespace std;

namespace {
void print_card_option(int option, const Card &card) {
    cout << option << ". [" << card.getType() << "] "
         << card.getName()
         << " (" << card.getCost() << ") - "
         << card.getDescription();

    if(card.getIsApplyToEnemy()) {
        cout << " Target enemy.";
    }

    cout << "\n";
}

void print_enemy_status(int option, const Enemy &enemy) {
    cout << option << ". " << enemy.name
         << " HP " << enemy.hp << "/" << enemy.max_hp
         << " | Armor " << enemy.armor
         << " | Next attack " << enemy.attack << "\n";
}
}

void Battle::start_combat(bool boss_battle) {
    is_boss_battle = boss_battle;
    round = BattleRound::select_option;
    player.hand.clear();
    player.discard_pile.clear();
    player.draw_pile = player.cards;
    shuffleDeck(player.draw_pile);
    start_player_turn();
}

void Battle::draw_cards(int count) {
    while(count > 0 && player.hand.size() < static_cast<size_t>(player.max_card)) {
        if(player.draw_pile.empty()) {
            if(player.discard_pile.empty()) {
                return;
            }
            player.draw_pile = player.discard_pile;
            player.discard_pile.clear();
            shuffleDeck(player.draw_pile);
        }

        player.hand.push_back(player.draw_pile.back());
        player.draw_pile.pop_back();
        --count;
    }
}

void Battle::discard_hand() {
    player.discard_pile.insert(player.discard_pile.end(), player.hand.begin(), player.hand.end());
    player.hand.clear();
}

void Battle::start_player_turn() {
    player.energy = player.max_energy;
    player.block = 0;
    draw_cards(5);
}

void Battle::finish_victory() {
    discard_hand();
    player.draw_pile.clear();
    player.discard_pile.clear();
    player.block = 0;

    int battle_score = 100 + (player.stage * 10);
    current_score += battle_score;
    cout << "\nBattle won. Score +" << battle_score
         << " | Total score " << current_score << "\n";

    player.stage++;

    if(is_boss_battle) {
        current_run_won = true;
        record_current_run();
        cur_screen = Screen::end;
        return;
    }

    vector<Card> rewards = Cardfactory::create_reward_card(3);
    cout << "\nChoose a reward card:\n";
    for(size_t i = 0; i < rewards.size(); ++i) {
        print_card_option(static_cast<int>(i + 1), rewards[i]);
    }
    cout << "4. Skip\n";
    cout << "Choose: ";

    int choice = read_int();
    if(choice >= 1 && choice <= static_cast<int>(rewards.size())) {
        player.cards.push_back(rewards[choice - 1]);
        cout << rewards[choice - 1].getName() << " added to your deck.\n";
    }
    else {
        cout << "You keep your deck unchanged.\n";
    }

    player.heal(5);
    cout << "You recover 5 HP. Player HP " << player.hp << "/" << player.max_hp << ".\n";
    save_current_game();
    cur_screen = Screen::map;
}

void Battle::print_and_select_options() {
    for(int i = 0; i < enemies.size(); ) {
        if(enemies[i].is_dead()) {
            enemies.erase(enemies.begin() + i);
        }
        else {
            ++i;
        }
    }

    if(enemies.empty()) { // victory
        round = BattleRound::victory;
        finish_victory();
        return;
    }

    cout << "\nPlayer HP " << player.hp << "/" << player.max_hp
         << " | Block " << player.block
         << " | Energy " << player.energy << "/" << player.max_energy
         << " | Stage " << player.stage
         << " | Score " << current_score << "\n";
    cout << "Deck " << player.cards.size()
         << " | Draw " << player.draw_pile.size()
         << " | Discard " << player.discard_pile.size() << "\n";

    for(size_t i = 0; i < enemies.size(); ++i) {
        const Enemy &enemy = enemies[i];
        cout << enemy.name << " HP " << enemy.hp << "/" << enemy.max_hp
             << " | Armor " << enemy.armor
             << " | Next attack " << enemy.attack << "\n";
    }

    cout << "Hand:\n";
    valid_options.clear();
    int option_name = 1;

    if(player.hand.empty()) {
        cout << "No cards in hand. End the turn to draw again.\n";
    }

    for(int i = 0; i < player.hand.size(); ++i) {
        const Card &card = player.hand[i];

        print_card_option(option_name, card);
        
        valid_options[to_string(option_name)] = [&, i]() {  // Capture i by value to avoid reference issues
            print_sep_line();

            if(i < 0 || i >= static_cast<int>(player.hand.size())) {
                cout << "Invalid card index!\n";
                return;
            }

            const Card &selected_card = player.hand[i];
            if(!selected_card.isPlayable(player.energy)) {
                cout << "Not enough energy to play " << selected_card.getName() << "!\n";
                return;
            }
            player.energy -= selected_card.getCost();

            round = BattleRound::select_option;
            played_card_idx = i;
            cout << selected_card.getName() << " played.\n";

            if(!selected_card.getIsApplyToEnemy()) {
                played_card_enemy_idx = -1;  // index = -1 for non-target cards
                apply_card();
                return;
            }

            // else: card applies to enemy
            cout << "\nChoose target for " << selected_card.getName() << ":\n";
            for(size_t j = 0; j < enemies.size(); ++j) {
                print_enemy_status(static_cast<int>(j + 1), enemies[j]);
            }
            cout << "Choose: ";

            int option_enemy_idx = read_int();
            while(!(1 <= option_enemy_idx && option_enemy_idx <= static_cast<int>(enemies.size()))) {
                cout << "Invalid enemy index!\n";
                cout << "Choose target between 1 and " << enemies.size() << ": ";
                option_enemy_idx = read_int();
            }

            played_card_enemy_idx = option_enemy_idx - 1;  // convert from 1-based to 0-based index
            apply_card();
        };
        ++option_name;
    }

    cout << option_name << ". End turn\n";
    cout << "Choose: ";
    valid_options[to_string(option_name)] = [&]() {
        cout << "Turn ended.\n";
        discard_hand();
        round = BattleRound::option_result;
    };
}

void Battle::print_and_apply_enemies() {
    for(int i = 0; i < enemies.size(); ) { // remove dead enemies first
        if(enemies[i].is_dead()) {
            enemies.erase(enemies.begin() + i);
        }
        else {
            ++i;
        }
    }
    if(enemies.empty()) {
        cout << "No enemies remain.\n";
        return;
    }

    for(int i = 0; i < enemies.size(); ++i) {
        const Enemy &enemy = enemies[i];

        const int old_player_hp = player.hp;
        int damage = enemy.get_attack();
        if(player.block >= damage) {
            player.block -= damage;
            damage = 0;
        }
        else {
            damage -= player.block;
            player.block = 0;
        }
        player.hurt(damage);
        cout << enemy.name << " attacks for " << enemy.get_attack()
             << ". You lose " << (old_player_hp - player.hp)
             << " HP after block.\n";

        if(player.is_dead()) {
            current_run_won = false;
            record_current_run();
            cur_screen = Screen::end;
            break;
        }
    }
}

void Battle::print_battle_screen() {
    switch(round) {
    case BattleRound::select_option: {
        print_and_select_options();
        break;
    }
    case BattleRound::option_result: {
        print_and_apply_enemies();
        break;
    }
    case BattleRound::victory: {
        cur_screen = Screen::map;
        break;
    }
    default: {
        cout << "Unimplemented battle round!\n";
        break;
    }
    }
}

void Battle::process_player_input() {
    switch(round) {
    case BattleRound::select_option: {
        string option;
        cin >> option;
        if(valid_options.find(option) == valid_options.end()) { // can't find this option
            cout << "Invalid option!\n";
            return;
        }

        // else run the option function
        valid_options[option]();
        break;
    }
    case BattleRound::option_result: {
        if(cur_screen == Screen::battle) {
            start_player_turn();
            round = BattleRound::select_option;
        }
        break;
    }
    case BattleRound::victory: {
        break;
    }
    default: {
        cout << "Unimplemented battle round!\n";
        break;
    }
    }
}

void Battle::apply_card() {
    if(played_card_idx < 0 || played_card_idx >= static_cast<int>(player.hand.size())) {
        cout << "Invalid card index!\n";
        return;
    }

    Card card = player.hand[played_card_idx];

    if(card.getIsApplyToEnemy()) {
        if(played_card_enemy_idx < 0 || played_card_enemy_idx >= static_cast<int>(enemies.size())) { // invalid enemy
            cout << "Invalid enemy index!\n";
            return;
        }
        Enemy &enemy = enemies[played_card_enemy_idx];

        if(card.getType() == "Attack") {
            int damage = player.get_damage(card.getValue());
            cout << "You deal " << damage << " damage to " << enemy.name << ".\n";
            enemy.take_damage(damage);
            if(card.getName() == "Quick Slash") {
                player.block += 2;
                cout << "You gained 2 block.\n";
            }
            if(enemy.is_dead()) {
                cout << enemy.name << " is defeated.\n";
            }
        }
    }
    else { // card doesn't apply to enemy
        if(card.getName() == "Defend") {
            cout << "You gained " << card.getValue() << " block.\n";
            player.block += card.getValue();
        }
        else if(card.getName() == "Heal") {
            cout << "You healed for " << card.getValue() << " HP.\n";
            player.heal(card.getValue());
        }
        else if(card.getName() == "Recover") {
            cout << "You recovered " << card.getValue() << " energy.\n";
            player.energy += card.getValue();
            if(player.energy > player.max_energy) {
                player.energy = player.max_energy;
            }
        }
        else if(card.getName() == "Iron Wall") {
            cout << "You gained " << card.getValue() << " block.\n";
            player.block += card.getValue();
        }
        else if(card.getName() == "Adrenaline") {
            player.energy += 1;
            if(player.energy > player.max_energy) {
                player.energy = player.max_energy;
            }
            player.heal(2);
            cout << "You gained 1 energy and recovered 2 HP.\n";
        }
    }

    player.hand.erase(player.hand.begin() + played_card_idx);
    player.discard_pile.push_back(card);
}
