#ifndef REWARD_SCREEN_H
#define REWARD_SCREEN_H

#include "player.h"

using namespace std;

void show_reward_screen(Player& player, int& score);  // Display after battle
void show_score_summary(int score, int floor, int difficulty);  // End game stats

#endif