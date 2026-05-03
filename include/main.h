#ifndef MAIN_H
#define MAIN_H

#include "battle.h"
#include "map.h"

#include <string>

// Safer integer input helper used by most menus.
int read_int();

// Just prints a blank line, but keeps screens looking consistent.
void print_sep_line();

// The whole program moves between these screens.
enum class Screen { welcome, lobby, map, battle, end, quit };

// Older enum kept around; the actual chosen difficulty is stored as an int.
enum class Difficulty { easy, normal, hard, lunatic };

// Main game globals. Small terminal project, so this keeps screen functions simple.
extern bool is_game_running;
extern int difficulty;
extern int current_score;
extern bool current_run_won;
extern bool record_saved;
extern Screen cur_screen;
extern Battle cur_battle;
extern Map cur_map;
extern std::string game_save_file;
extern std::string record_save_file;

// Main menu screen.
void welcome_screen();

// New-run / save selection screen.
void lobby_screen();

// Map movement screen.
void map_screen();

// Combat screen.
void battle_screen();

// Win/loss screen.
void end_screen();

// New run menu.
void save_slot_screen();

// Show best score and win/loss record.
void record_screen();

// Show every card template.
void card_library_screen();

// Print short instructions.
void info_screen();

// Save current run to file.
void save_current_game();

// Load current run from file, if possible.
bool load_current_game();

// Write final run result to the long-term record.
void record_current_run();

// Finish the current run as a player death.
void player_died();

#endif // ifndef MAIN_H
