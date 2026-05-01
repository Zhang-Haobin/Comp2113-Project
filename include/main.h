#ifndef MAIN_H
#define MAIN_H

#include "battle.h"

int read_int();
void print_sep_line();

enum class Screen { welcome, lobby, map, battle, end, quit };
enum class Difficulty { easy, normal, hard, lunatic };

extern bool is_game_running;
extern int difficulty;
extern Screen cur_screen;
extern Battle cur_battle;

void welcome_screen();
void lobby_screen();
void map_screen();
void battle_screen();
void end_screen();

void save_slot_screen();
void record_screen();
void info_screen();

#endif // ifndef MAIN_H
