#ifndef BATTLE_H
#define BATTLE_H

#include <vector>

#include "player.h"
#include "enemy.h"

// a "screen", initialized by the main loop

class Battle {
public:
	Player player;
	vector<Enemy> enemies;

	void print_battle_screen() {
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
}

#endif // ifndef BATTLE_H
