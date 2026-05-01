#ifndef COMBAT_UTILS_H
#define COMBAT_UTILS_H

#include "player.h"
#include "enemy.h"
#include "battle.h"

using namespace std;

void reset_player_turn(Player &player);  // Reset energy, draw cards
void draw_cards(Player &player, int count);  // Draw from deck to hand
void apply_enemy_attack(Player &player, const Enemy &enemy);  // Damage with block
bool is_battle_over(const Battle &battle);  // Check win/loss condition
void grant_battle_rewards(Player &player, int &score);  // Give rewards after win
void end_player_turn(Player &player);  // Clear block, end effects

#endif
