#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>

#include "../include/battle.h"
#include "../include/main.h"
#include "../include/save.h"

using namespace std;

void Battle::print_and_select_options() {
    cout << player.name << " HP " << player.hp << "/" << player.max_hp << " | Block 0 | Energy " << player.energy << " | Potions 0\n\n";

    if(enemies.empty()) {
        cout << "(Silence... No enemies present)\n\n";
    }
    else {
        for(const Enemy &enemy : enemies) {
            cout << enemy.name << " HP " << enemy.hp << "/" << enemy.max_hp << " | Next attack " << enemy.attack << "\n";
        }
        cout << "\n";
    }

    cout << "Hand:\n\n";
    valid_options.clear();
    int option_name = 1;

    if(player.cards.empty()) {
        cout << "(You don't have any cards)\n\n";
        return;
    }
    // else:

    for(int i = 0; i < player.cards.size(); ++i) {
        const Card &card = player.cards[i];

        // Print card name, cost, and description
        cout << option_name << ". " << card.getName() << " (Cost: " << card.getCost() << ") - " << card.getDescription() << "\n";
        
        valid_options[to_string(option_name)] = [&, i]() {  // Capture i by value to avoid reference issues
            if(!card.isPlayable(player.energy)) {
                cout << "Not enough energy to play " << card.getName() << "!\n";
                return;
            }
            player.energy -= card.getCost();

            round = BattleRound::option_result;
            played_card_idx = i;
            cout << "You played " << card.getName() << "!\n";

            if(!card.getIsApplyToEnemy()) {
                // Card doesn't need target (like Defend or Heal)
                played_card_enemy_idx = -1;  // Set to -1 for non-target cards
                apply_card();
                return;
            }

            // Card needs a target - ask player which enemy to target
            cout << "Apply '" << card.getName() << "' to which enemy?\n\n";
            for(int j = 0; j < enemies.size(); ++j) {
                Enemy &enemy = enemies[j];
                cout << j + 1 << ". " << enemy.name << " HP " << enemy.hp << "/" << enemy.max_hp << " | Next attack " << enemy.attack << "\n";
            }

            int option_enemy_idx = read_int();
            while(!(1 <= option_enemy_idx && option_enemy_idx <= enemies.size())) {
                cout << "Invalid enemy index!\n";
                cout << "Apply '" << card.getName() << "' to which enemy?\n";
                option_enemy_idx = read_int();
            }

            played_card_enemy_idx = option_enemy_idx - 1;  // Convert to 0-based index
            apply_card();
        };
        ++option_name;
    }

    cout << "\n" << option_name << ". End turn\n\n";
    valid_options[to_string(option_name)] = [&]() {
        round = BattleRound::option_result; // do nothing
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
    for(int i = 0; i < enemies.size(); ++i) {
        const Enemy &enemy = enemies[i];

        const int old_player_hp = player.hp;
        player.hurt(enemy.get_attack());
        cout << enemy.name << " dealt " << (old_player_hp - player.hp) << " damage to you!\n\n";

        if(player.is_dead()) {
            cur_screen = Screen::end;
            break;
        }
    }
    cout << "Press enter to continue...\n";
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    round = BattleRound::select_option;
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
    default: {
        cout << "Unimplemented battle round!\n";
        break;
    }
    }
}

void Battle::process_player_input() {
    // todo: save the current battle state every turn
    switch(round) {
    case BattleRound::select_option: {
        string option;
        cin >> option;

        if(valid_options.find(option) == valid_options.end()) { // can't find this option
            cout << "'" << option << "' is not a valid option!\n";
            return;
        }

        // else run the option function
        valid_options[option]();
        break;
    }
    case BattleRound::option_result: {
        string input;
        cin >> input;
        round = BattleRound::select_option;
        break;
    }
    }
}

void Battle::apply_card() {
    const Card &card = player.cards[played_card_idx];
    
    cout << "You performed " << card.getName();
    
    // Check if card applies to enemy (for damage cards)
    if(card.getIsApplyToEnemy() && played_card_enemy_idx != -1 && played_card_enemy_idx < enemies.size()) {
        Enemy &enemy = enemies[played_card_enemy_idx];
        cout << " on " << enemy.name;
        cout << "!\n\n";

        // Apply damage effects
        if(card.getType() == "Strike" || card.getType() == "Attack") {
            cout << "You dealt " << card.getValue() << " damage to " << enemy.name << "!\n";
            enemy.take_damage(card.getValue());
            if(enemy.is_dead()) {
                cout << enemy.name << " is defeated!\n";
            }
        }
        else if(card.getType() == "Bash") {
            cout << "You dealt " << card.getValue() << " damage to " << enemy.name << "!\n";
            enemy.take_damage(card.getValue());
            if(enemy.is_dead()) {
                cout << enemy.name << " is defeated!\n";
            }
        }
        else if(card.getType() == "Fireball") {
            cout << "You dealt " << card.getValue() << " damage to " << enemy.name << "!\n";
            enemy.take_damage(card.getValue());
            if(enemy.is_dead()) {
                cout << enemy.name << " is defeated!\n";
            }
        }
        else if(card.getType() == "Quick Slash") {
            cout << "You dealt " << card.getValue() << " damage to " << enemy.name << "!\n";
            enemy.take_damage(card.getValue());
            if(enemy.is_dead()) {
                cout << enemy.name << " is defeated!\n";
            }
        }
    }
    else {
        // Card doesn't apply to enemy (like Defend or Heal)
        cout << "!\n\n";

        if(card.getType() == "Defend") {
            cout << "You gained " << card.getValue() << " block!\n";
            player.block += card.getValue();
        }
        else if(card.getType() == "Heal") {
            cout << "You healed for " << card.getValue() << " HP!\n";
            player.heal(card.getValue());
        }
        else if(card.getType() == "Recover") {
            cout << "You recovered " << card.getValue() << " energy!\n";
            player.energy += card.getValue();
            if(player.energy > player.max_energy) {
                player.energy = player.max_energy;
            }
        }
        else if(card.getType() == "Iron Wall") {
            cout << "You gained " << card.getValue() << " block!\n";
            player.block += card.getValue();
        }
        else if(card.getType() == "Adrenaline") {
            player.energy += 1;
            if(player.energy > player.max_energy) {
                player.energy = player.max_energy;
            }
            player.heal(2);
            cout << "You gained 1 energy and recovered 2 HP!\n";
        }
    }

    // actually consume that card
    player.cards.erase(player.cards.begin() + played_card_idx);
}
