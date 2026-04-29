#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "battle.h"
#include "save.h"

using namespace std;

void Battle::print_battle_screen() {
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
		for(const Card &card : player.cards) {
			cout << option_name << ". \n\n"; // todo
			valid_options.push_back(to_string(option_name));
			++option_name;
		}
	}
	cout << option_name << ". End turn\n\n";
	valid_options.push_back(to_string(option_name));
	++option_name;

	cout << option_name << ". Drink potion\n\n";
	valid_options.push_back(to_string(option_name));
}

void Battle::process_player_input() {
	// todo: save the current battle state every turn

	string option;
	cin >> option;

	auto option_it = find(valid_options.begin(), valid_options.end(), option); // iterator; typename too complex
	if(option_it != valid_options.end()) { // COULDN'T find this player-input option
		cout << "'" << option << "' is not a valid option!\n";
		return;
	}
	// else:

	;
}
