#ifndef MAIN_H
#define MAIN_H

enum class Screen { welcome, lobby, map, battle, paused, end };
enum class Difficulty { easy, normal, hard, lunatic }; 

bool is_game_running = true;
int difficulty = 2;
Screen cur_screen = Screen::welcome;

void welcome_screen();                              
void lobby_screen();
void map_screen();
void battle_screen();
void paused_screen();

void save_slot_screen();
void record_screen();
void info_screen();

#endif // ifndef MAIN_H
