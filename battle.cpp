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
		for(const Card &card : player.cards) {
			cout << option_name << ". \n\n"; // todo
			valid_options[to_string(option_name)] = [&]() {
				if(!card.isPlayable(player.energy)) {
					cout << "Not enough energy to play " << card.getName() << "!\n";
					return;
				}
				player.energy -= card.getCost();

				cout << "You played " << card.getName() << "!\n";
				round = BattleRound::option_result;
				// todo: implement card effects
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
	cout << "You performed" << 123 /* todo */ << "!" << "\n";
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
