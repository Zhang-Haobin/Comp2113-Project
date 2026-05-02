#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <string>

#include "player.h"
#include "map.h"

using namespace std;

struct GameState {
    Player player;
    Map current_map;
    int score;
    int current_floor;
    bool is_boss_fight;
    
    GameState();
    
    void save_to_file(const string& filename);   // Write to file
    bool load_from_file(const string& filename); // Read from file
    void reset();                                 // Clear all data
};

#endif
