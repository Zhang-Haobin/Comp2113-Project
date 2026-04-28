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

	void print_battle_screen() const;
}

#endif // ifndef BATTLE_H
