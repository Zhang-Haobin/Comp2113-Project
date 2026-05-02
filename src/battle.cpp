#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <thread>

#include "../include/battle.h"
#include "../include/main.h"
#include "../include/save.h"
#include "../include/Cardfactory.h"
#include "../include/Deck.h"
#include "../include/difficulty.h"

using namespace std;

namespace {
const string COLOR_RESET = "\033[0m";
const string COLOR_RED = "\033[31m";
const string COLOR_GREEN = "\033[32m";
const string COLOR_YELLOW = "\033[33m";
const string COLOR_BLUE = "\033[34m";
const string COLOR_CYAN = "\033[36m";

string card_type_color(const string &type) {
    if(type == "Attack") return COLOR_RED;
    if(type == "Skill") return COLOR_BLUE;
    if(type == "Utility") return COLOR_GREEN;
    return "";
}

bool is_aoe_attack(const Card &card) {
    return card.getName() == "Cleave";
}

void print_padded_colored(const string &text, int width, const string &color) {
    if(color.empty()) {
        cout << text;
    }
    else {
        cout << color << text << COLOR_RESET;
    }
    if(static_cast<int>(text.size()) < width) {
        cout << string(width - text.size(), ' ');
    }
}

// Print one card as a numbered menu option.
void print_card_option(int option, const Card &card, int current_energy = -1) {
    string type_label = "[" + card.getType() + "]";
    bool cannot_afford = current_energy >= 0 && !card.isPlayable(current_energy);

    cout << left
         << setw(4) << (to_string(option) + ".");
    print_padded_colored(type_label, 11, card_type_color(card.getType()));
    cout << setw(12) << card.getName()
         << "(" << card.getCost() << ") - "
         << card.getDescription();

    if(card.getIsApplyToEnemy()) {
        cout << " Target enemy.";
    }
    if(cannot_afford) {
        cout << " " << COLOR_YELLOW << "Not enough energy." << COLOR_RESET;
    }

    cout << right << "\n";
}

// Enemy target list uses this format when an attack card needs a target.
void print_enemy_status(int option, const Enemy &enemy) {
    cout << option << ". " << enemy.name
         << " HP " << COLOR_RED << enemy.hp << "/" << enemy.max_hp << COLOR_RESET
         << " | Armor " << enemy.armor
         << " | Next attack " << enemy.attack << "\n";
}

void print_action_status(const Player &player, const vector<Enemy> &enemies) {
    cout << "\nEnemy status:\n";
    bool any_alive = false;
    for(const Enemy &enemy : enemies) {
        if(enemy.is_dead()) {
            cout << enemy.name << " defeated.\n";
        }
        else {
            any_alive = true;
            cout << enemy.name << " HP " << COLOR_RED << enemy.hp << "/" << enemy.max_hp << COLOR_RESET
                 << " | Armor " << enemy.armor
                 << " | Next attack " << enemy.attack << "\n";
        }
    }
    if(!any_alive) {
        cout << "All enemies defeated.\n";
    }

    cout << "Player HP " << COLOR_RED << player.hp << "/" << player.max_hp << COLOR_RESET
         << " | Block " << COLOR_CYAN << player.block << COLOR_RESET
         << " | Energy " << COLOR_YELLOW << player.energy << "/" << player.max_energy << COLOR_RESET << "\n";
}

void wait_for_next_screen(int milliseconds = 1000) {
    cout.flush();
    this_thread::sleep_for(chrono::milliseconds(milliseconds));
}
}

// Fresh combat setup: reset piles, shuffle deck, then start the player's first turn.
void Battle::start_combat(bool boss_battle) {
    is_boss_battle = boss_battle;
    round = BattleRound::select_option;
    player.hand.clear();
    player.discard_pile.clear();
    player.draw_pile = player.cards;
    shuffleDeck(player.draw_pile);
    start_player_turn();
}

// Draw from draw pile. If it runs out, shuffle discard pile back in.
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

// At end of turn or combat, move hand cards away.
void Battle::discard_hand() {
    player.discard_pile.insert(player.discard_pile.end(), player.hand.begin(), player.hand.end());
    player.hand.clear();
}

// New player turn means full energy, no old block, and a fresh draw.
void Battle::start_player_turn() {
    player.energy = player.max_energy;
    player.block = 0;
    draw_cards(5);
}

// Called when all enemies are defeated.
void Battle::finish_victory() {
    discard_hand();
    player.draw_pile.clear();
    player.discard_pile.clear();
    player.block = 0;

    DifficultySettings settings = get_difficulty_by_level(player.difficulty);
    int battle_score = static_cast<int>((100 + (player.stage * 10)) * settings.score_multiplier);
    current_score += battle_score;
    cout << "\nBattle won. Score +" << battle_score
         << " | Total score " << current_score << "\n";

    player.stage++;

    if(is_boss_battle) {
        Card rare_reward = Cardfactory::create_random_rare_card();
        player.cards.push_back(rare_reward);
        cout << "Boss reward: " << rare_reward.getName()
             << " added to your deck as a rare card.\n";
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

// Main player-choice screen for battle.
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

    cout << "\nPlayer HP " << COLOR_RED << player.hp << "/" << player.max_hp << COLOR_RESET
         << " | Block " << COLOR_CYAN << player.block << COLOR_RESET
         << " | Energy " << COLOR_YELLOW << player.energy << "/" << player.max_energy << COLOR_RESET
         << " | Stage " << player.stage
         << " | Score " << current_score << "\n";
    cout << "Deck " << player.cards.size()
         << " | Draw " << player.draw_pile.size()
         << " | Discard " << player.discard_pile.size() << "\n";

    for(size_t i = 0; i < enemies.size(); ++i) {
        const Enemy &enemy = enemies[i];
        cout << enemy.name << " HP " << COLOR_RED << enemy.hp << "/" << enemy.max_hp << COLOR_RESET
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

        print_card_option(option_name, card, player.energy);
        
        valid_options[to_string(option_name)] = [&, i]() {  // capture i by value, otherwise menu choices point at the wrong card
            print_sep_line();

            if(i < 0 || i >= static_cast<int>(player.hand.size())) {
                cout << "Invalid card index!\n";
                return;
            }

            const Card &selected_card = player.hand[i];
            if(!selected_card.isPlayable(player.energy)) {
                cout << "Action Log\n";
                cout << "Not enough energy to play " << selected_card.getName()
                     << ". Need " << selected_card.getCost()
                     << ", but you have " << player.energy << ".\n";
                return;
            }
            player.energy -= selected_card.getCost();

            round = BattleRound::select_option;
            played_card_idx = i;

            if(is_aoe_attack(selected_card)) {
                played_card_enemy_idx = -1;
                cout << "Action Log\n";
                cout << "You played " << selected_card.getName() << " on all enemies.\n";
                apply_card();
                return;
            }

            if(!selected_card.getIsApplyToEnemy()) {
                played_card_enemy_idx = -1;  // index = -1 for non-target cards
                cout << "Action Log\n";
                cout << "You played " << selected_card.getName() << ".\n";
                apply_card();
                return;
            }

            if(enemies.size() == 1) {
                played_card_enemy_idx = 0;
                cout << "Action Log\n";
                cout << "You played " << selected_card.getName()
                     << " on " << enemies[played_card_enemy_idx].name << ".\n";
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
            cout << "\nAction Log\n";
            cout << "You played " << selected_card.getName()
                 << " on " << enemies[played_card_enemy_idx].name << ".\n";
            apply_card();
        };
        ++option_name;
    }

    cout << option_name << ". End turn\n";
    cout << "Choose: ";
    valid_options[to_string(option_name)] = [&]() {
        cout << "Turn ended.\n";
        discard_hand();
        keep_next_battle_screen = true;
        round = BattleRound::option_result;
    };
}

// Enemy phase after the player ends the turn.
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

    cout << "Enemy Turn\n";
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
             << ". Block absorbs " << (enemy.get_attack() - damage)
             << ", you lose " << (old_player_hp - player.hp) << " HP.\n";

        if(player.is_dead()) {
            current_run_won = false;
            record_current_run();
            cur_screen = Screen::end;
            break;
        }
    }

    if(cur_screen == Screen::battle) {
        print_action_status(player, enemies);
        keep_next_battle_screen = true;
    }
}

// Decide which battle sub-screen should be printed.
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

// Read one battle input and run the option stored in valid_options.
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
        if(round == BattleRound::select_option || cur_screen != Screen::battle) {
            print_action_status(player, enemies);
            keep_next_battle_screen = true;
            wait_for_next_screen();
        }
        break;
    }
    case BattleRound::option_result: {
        wait_for_next_screen(2000);
        if(cur_screen == Screen::battle) {
            start_player_turn();
            keep_next_battle_screen = true;
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

// Resolve the selected card. Card data is simple; the real effects are checked here.
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
            int base_damage = card.getValue();

            if(card.getName() == "Perfected Strike") {
                int bonus = 0;
                for(const Card &deck_card : player.cards) {
                    if(deck_card.getName().find("Strike") != string::npos) {
                        bonus += 2;
                    }
                }
                base_damage = 6 + bonus;
                cout << "Perfected Strike gains +" << bonus << " damage from your deck.\n";
            }
            else if(card.getName() == "Rampage") {
                base_damage = 8 + (card.times_played * 5);
                cout << "Rampage has been played " << card.times_played
                     << " time(s) this battle.\n";
            }

            int damage = player.get_damage(base_damage);
            int old_enemy_hp = enemy.hp;
            int damage_after_armor = max(0, damage - enemy.armor);
            int armor_blocked = damage - damage_after_armor;
            enemy.take_damage(damage);
            cout << enemy.name << " takes " << (old_enemy_hp - enemy.hp)
                 << " damage";
            if(armor_blocked > 0) {
                cout << " (" << armor_blocked << " blocked by armor)";
            }
            cout << ".\n";

            if(card.getName() == "Rampage") {
                card.times_played++;
                cout << "Rampage will deal 5 more damage next time this battle.\n";
            }

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
        if(is_aoe_attack(card)) {
            int damage = player.get_damage(card.getValue());
            for(Enemy &enemy : enemies) {
                if(enemy.is_dead()) {
                    continue;
                }

                int old_enemy_hp = enemy.hp;
                int damage_after_armor = max(0, damage - enemy.armor);
                int armor_blocked = damage - damage_after_armor;
                enemy.take_damage(damage);

                cout << enemy.name << " takes " << (old_enemy_hp - enemy.hp)
                     << " damage";
                if(armor_blocked > 0) {
                    cout << " (" << armor_blocked << " blocked by armor)";
                }
                cout << ".\n";

                if(enemy.is_dead()) {
                    cout << enemy.name << " is defeated.\n";
                }
            }
        }
        else if(card.getName() == "Defend") {
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
        else if(card.getName() == "Entrench") {
            int old_block = player.block;
            player.block *= 2;
            cout << "Entrench doubles your block from " << old_block
                 << " to " << player.block << ".\n";
        }
        else if(card.getName() == "Bloodletting") {
            player.hurt(3);
            player.energy += 2;
            cout << "Bloodletting costs 3 HP and gives 2 energy.\n";
            cout << "Player HP " << player.hp << "/" << player.max_hp
                 << " | Energy " << player.energy << "/" << player.max_energy << "\n";
        }
    }

    player.hand.erase(player.hand.begin() + played_card_idx);
    player.discard_pile.push_back(card);

    if(player.is_dead()) {
        current_run_won = false;
        record_current_run();
        cur_screen = Screen::end;
    }
}
