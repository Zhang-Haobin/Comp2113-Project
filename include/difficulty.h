#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <string>

using namespace std;

struct DifficultySettings {
    int level;
    string name;
    int map_layers;
    int player_max_hp;
    float enemy_hp_multiplier;
    float enemy_damage_multiplier;
    float score_multiplier;
    int starting_bonus;
};

DifficultySettings get_difficulty_by_level(int level);  // Get settings
void apply_difficulty_to_player(int level, class Player& player);  // Apply to player
void print_difficulty_options();  // Display menu

#endif