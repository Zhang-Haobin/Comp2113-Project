#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <string>

using namespace std;

// A small bundle of numbers for one difficulty choice.
// Some fields are here for possible balancing even if not every one is used yet.
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

DifficultySettings get_difficulty_by_level(int level);  // turn 1/2/3 into settings
void apply_difficulty_to_player(int level, class Player& player);  // put the settings onto the player
void print_difficulty_options();  // print the menu choices

#endif
