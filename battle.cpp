#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "battle.h"
#include "save.h"

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
        cout << "(You don't have any cards)\n";
    }
    else {
        for(int i = 0; i < player.cards.size(); ++i) {
            const Card &card = player.cards[i];

            cout << option_name << ". \n\n";
            
            valid_options[to_string(option_name)] = [&]() {
                if(!card.isPlayable(player.energy)) {
                    cout << "Not enough energy to play " << card.getName() << "!\n";
                    return;
                }
                player.energy -= card.getCost();

                round = BattleRound::option_result;
                played_card_idx = i;
                cout << "You played " << card.getName() << "!\n";

                if(!card.getIsApplyToEnemy()) {
                    apply_card();
                    return;
                }

                cout << "Apply '" << card.getName() << "' to which enemy?\n";
                for(int j = 0; j < enemies.size(); ++j) {
                    Enemy &enemy = enemies[j];
                    cout << j + 1 << ". " << enemy.name << " HP " << enemy.hp << "/" << enemy.max_hp << " | Next attack " << enemy.attack << "\n";
                }

                int option_enemy_idx;
                do {
                    cin >> option_enemy_idx;
                    if(!(1 <= option_enemy_idx && option_enemy_idx <= enemies.size())) {
                        cout << "Invalid enemy index!\n\n";
                        cout << "Apply '" << card.getName() << "' to which enemy?\n";
                    }
                } while(!(1 <= option_enemy_idx && option_enemy_idx <= enemies.size()));

                played_card_enemy_idx = option_enemy_idx - 1;
                apply_card();
            };
            ++option_name;
        }
    }

    cout << option_name << ". End turn\n\n";
    valid_options[to_string(option_name)] = [&]() {
        // end turn: do nothing
        round = BattleRound::option_result;
    };
    ++option_name;

    cout << option_name << ". Drink potion\n\n";
    valid_options[to_string(option_name)] = [&]() {
        // todo: does not have potion currently
        round = BattleRound::option_result;
    };
}

void Battle::print_option_result() const {
    // todo
    cout << "Press enter to continue...\n";
}

void Battle::print_battle_screen() {
    switch(round) {
    case BattleRound::select_option: {
        print_and_select_options();
        break;
    }
    case BattleRound::option_result: {
        print_option_result();
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

        if(valid_options.find(option) == valid_options.end()) { // can't find this player-input option
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
    Enemy &enemy = enemies[played_card_enemy_idx];

    cout << "You performed" << player.cards[played_card_idx].getName();
    if(played_card_enemy_idx != -1) {
        cout << " on " << enemies[played_card_enemy_idx].name;
    }
    cout << "!\n\n";

    if(card.getType() == "Strike") {
        enemy.take_damage(card.getValue());
        cout << "You dealt " << card.getValue() << " damage to " << enemy.name << "!\n";
    }
    else if(card.getType() == "Defend") {
        player.block += card.getValue();
        cout << "You gained " << card.getValue() << " block!\n";
    }
    else if(card.getType() == "Heal") {
        player.hp = player.get_hp_after_heal(card.getValue());
        cout << "You healed for " << card.getValue() << " HP!\n";
    }
    else if(card.getType() == "Bash") {
        enemy.take_damage(card.getValue());
        cout << "You dealt " << card.getValue() << " damage to " << enemy.name << "!\n";
    }
    else if(card.getType() == "Recover") {
        player.energy += card.getValue();
        if(player.energy > player.max_energy) {
            player.energy = player.max_energy;
        }
        cout << "You recovered " << card.getValue() << " energy!\n";
    }
    else if(card.getType() == "Fireball") {
        enemy.take_damage(card.getValue());
        cout << "You dealt " << card.getValue() << " damage to " << enemy.name << "!\n";
    }
    else if(card.getType() == "Quick Slash") {
        enemy.take_damage(card.getValue());
        cout << "You dealt " << card.getValue() << " damage to " << enemy.name << "!\n";
    }
    else if(card.getType() == "Iron Wall") {
        player.block += card.getValue();
        cout << "You gained " << card.getValue() << " block!\n";
    }
    else if(card.getType() == "Adrenaline") {
        card.getValue(); // todo: 2 stats?

        player.energy += 1;
        if(player.energy > player.max_energy) {
            player.energy = player.max_energy;
        }
        player.hp = player.get_hp_after_heal(2);

        // todo: print msg
    }
    else {
        cout << "Unimplemented card type!\n";
    }
}
