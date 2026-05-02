#ifndef BATTLE_H
#define BATTLE_H

#include <string>
#include <functional>
#include <unordered_map>

#include "player.h"
#include "enemy.h"

template <typename K, typename V>
using umap = unordered_map<K, V>;

// Battle has a few mini-states so the screen knows what to do 
enum class BattleRound {
    select_option,
    option_result,
    victory,
};

// One battle owns the player-in-combat state 
class Battle {
public:
    Player player = {};
    vector<Enemy> enemies;
    BattleRound round = BattleRound::select_option;
    bool is_boss_battle = false;
    bool keep_next_battle_screen = false;

    // Option text maps to action
    umap<string, function<void()>> valid_options;
    int played_card_idx;
    int played_card_enemy_idx;

    Battle() = default;

    // Set up a fresh fight, shuffle the deck, and draw the opening hand.
    void start_combat(bool boss_battle);

    // Show player choices and prepare the menu actions.
    void print_and_select_options();

    // Let enemies attack after the player ends the turn.
    void print_and_apply_enemies();

    // Print whatever part of the battle is currently active.
    void print_battle_screen();

    // Read the player's battle choice and run the matching action.
    void process_player_input();

    // Actually apply the chosen card effect.
    void apply_card();

    // Use and remove one potion from the player's potion slots.
    void use_potion(int potion_idx);

    // Draw cards from draw pile, reshuffling discard pile if needed.
    void draw_cards(int count);

    // Move the whole hand to discard pile.
    void discard_hand();

    // Reset energy/block and draw cards for a new player turn.
    void start_player_turn();

    // Give score and rewards after all enemies are defeated.
    void finish_victory();
};

#endif // ifndef BATTLE_H
