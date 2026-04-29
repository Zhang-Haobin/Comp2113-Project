#ifndef BATTLE_H
#define BATTLE_H

#include <string>
#include <vector>

#include "player.h"
#include "enemy.h"

// a "screen", initialized by the main loop

class Battle {
public:
	Player player;
	vector<Enemy> enemies;

	vector<string> valid_options;

	void print_battle_screen();
	void process_player_input();
};

#endif // ifndef BATTLE_H