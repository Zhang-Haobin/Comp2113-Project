#ifndef MAIN_H
#define MAIN_H

#include "battle.h"
#include "map.h"

int read_int();
void print_sep_line();

enum class Screen { welcome, lobby, map, battle, end, quit };
enum class Difficulty { easy, normal, hard, lunatic };

extern bool is_game_running;
extern int difficulty;
extern int current_score;
extern bool current_run_won;
extern bool record_saved;
extern Screen cur_screen;
extern Battle cur_battle;
extern Map cur_map;

void welcome_screen();
void lobby_screen();
void map_screen();
void battle_screen();
void end_screen();

void save_slot_screen();
void record_screen();
void info_screen();
void save_current_game();
bool load_current_game();
void record_current_run();

#endif // ifndef MAIN_H
