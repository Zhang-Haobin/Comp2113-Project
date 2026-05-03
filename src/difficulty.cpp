#include "../include/difficulty.h"
#include "../include/player.h"
#include "../include/main.h"
#include <iostream>

using namespace std;

// Convert menu choice into the actual difficulty numbers.
DifficultySettings get_difficulty_by_level(int level) {
    DifficultySettings s;
    s.level = level;
    
    if (level == 1) {
        s.name = "Easy";
        s.map_layers = 8;
        s.player_max_hp = 70;
        s.enemy_hp_multiplier = 0.8f;
        s.enemy_damage_multiplier = 0.8f;
        s.score_multiplier = 0.8f;
        s.starting_bonus = 100;
    }
    else if (level == 3) {
        s.name = "Hard";
        s.map_layers = 16;
        s.player_max_hp = 50;
        s.enemy_hp_multiplier = 1.4f;
        s.enemy_damage_multiplier = 1.3f;
        s.score_multiplier = 1.5f;
        s.starting_bonus = 0;
    }
    else { // Normal default
        s.name = "Normal";
        s.map_layers = 12;
        s.player_max_hp = 60;
        s.enemy_hp_multiplier = 1.0f;
        s.enemy_damage_multiplier = 1.0f;
        s.score_multiplier = 1.0f;
        s.starting_bonus = 0;
    }
    return s;
}

// Apply the chosen difficulty directly to the player.
void apply_difficulty_to_player(int level, Player& player) {
    DifficultySettings s = get_difficulty_by_level(level);
    player.max_hp = s.player_max_hp;
    player.hp = player.max_hp;
    player.difficulty = level;
    cout << "Difficulty: " << s.name
         << " | HP: " << player.hp
         << " | Floors: " << s.map_layers
         << " | Enemy HP x" << s.enemy_hp_multiplier
         << " | Enemy damage x" << s.enemy_damage_multiplier
         << " | Score x" << s.score_multiplier << "\n";
}

// Print difficulty menu before a new run starts.
void print_difficulty_options() {
    print_sep_line();
    cout << "=== Select Difficulty ===\n\n";
    for(int level = 1; level <= 3; ++level) {
        DifficultySettings s = get_difficulty_by_level(level);
        cout << "  " << level << ". " << s.name
             << " | Player HP " << s.player_max_hp
             << " | Floors " << s.map_layers
             << " | Enemy HP x" << s.enemy_hp_multiplier
             << " | Enemy damage x" << s.enemy_damage_multiplier
             << " | Score x" << s.score_multiplier << "\n";
    }
    cout << "\nEnter choice: ";
}
