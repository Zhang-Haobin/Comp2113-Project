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

void Battle::print_and_apply_enemies() {
    for(int i = 0; i < enemies.size(); ++i) {
        const Enemy &enemy = enemies[i];
        if(enemy.is_dead()) {
            continue;
        }

        const int old_player_hp = player.hp;
        player.hurt(enemy.get_attack());
        cout << enemy.name << " dealt " << (old_player_hp - player.hp) << " damage to you!\n\n";

        if(player.hp <= 0) {
            // todo
            break;
        }
    }
    cout << "Press enter to continue...\n";
    string dummy;
    getline(cin, dummy);
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
        cout << "You dealt " << card.getValue() << " damage to " << enemy.name << "!\n";

        enemy.take_damage(card.getValue());
        if(enemy.is_dead()) {
            cout << enemy.name << " is defeated!\n";
        }
    }
    else if(card.getType() == "Defend") {
        cout << "You gained " << card.getValue() << " block!\n";
        player.block += card.getValue();
    }
    else if(card.getType() == "Heal") {
        cout << "You healed for " << card.getValue() << " HP!\n";
        player.heal(card.getValue());
    }
    else if(card.getType() == "Bash") {
        cout << "You dealt " << card.getValue() << " damage to " << enemy.name << "!\n";

        enemy.take_damage(card.getValue());
        if(enemy.is_dead()) {
            cout << enemy.name << " is defeated!\n";
        }
    }
    else if(card.getType() == "Recover") {
        cout << "You recovered " << card.getValue() << " energy!\n";

        player.energy += card.getValue();
        if(player.energy > player.max_energy) {
            player.energy = player.max_energy;
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
    else if(card.getType() == "Iron Wall") {
        cout << "You gained " << card.getValue() << " block!\n";

        player.block += card.getValue();
    }
    else if(card.getType() == "Adrenaline") {
        card.getValue(); // todo: 2 stats?

        player.energy += 1;
        if(player.energy > player.max_energy) {
            player.energy = player.max_energy;
        }
        player.heal(2);

        // todo: print msg
    }
    else {
        cout << "Unimplemented card type!\n";
    }
}
