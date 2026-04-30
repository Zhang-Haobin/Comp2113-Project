#ifndef BATTLE_H
#define BATTLE_H

#include <string>
#include <functional>
#include <unordered_map>

#include "player.h"
#include "enemy.h"

template <typename K, typename V>
using umap = unordered_map<K, V>;

// a "screen", initialized by the main loop

enum class BattleRound {
    select_option,
    option_result,
};

class Battle {
public:
    Player player;
    vector<Enemy> enemies;
    BattleRound round = BattleRound::select_option;

    umap<string, function<void()>> valid_options;
    int played_card_idx;
    int played_card_enemy_idx;

    Battle() = default;

    void print_and_select_options();
    void print_option_result() const;
    void print_battle_screen();
    void process_player_input();

    void apply_card();
};

#endif // ifndef BATTLE_H
