#include <iostream>
#include <fstream>

#include "battle.h"
#include "save.h"

using namespace std;

Battle::print_battle_screen() {
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
	int option_name = 1;

	if(player.cards.empty()) {
		cout << "(You don't have any cards)\n";
	}
	else {
		for(const Card &card : player.cards) {
			cout << option_name << ". \n\n"; // todo
			++option_name;
		}
	}
	cout << option_name << ". End turn\n\n";
	++option_name;
	cout << option_name << ". Drink potion\n\n";
}

Battle::process_player_input() {
	// todo: save the current battle state every turn

	string ln;
	cin >> ln;

	try {
		int option = stoi(ln);
		if(option) { // todo
			throw exception();
		}

		
	}
	catch(exception e) {

	}
}
