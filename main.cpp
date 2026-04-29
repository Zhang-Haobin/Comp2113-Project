#include <iostream>
#include <string>

#include "main.h"
#include "player.h"
#include "save.h"
#include "battle.h"
#include "map.h"

using namespace std;

int main() {
    while(is_game_running) {
        switch(cur_screen) {
        case Screen::welcome:
            welcome_screen();
            break;
        case Screen::lobby:
            lobby_screen();
            break;
        case Screen::map:
            map_screen();
            break;
        case Screen::battle:
            battle_screen();
            break;
        case Screen::paused:
            paused_screen();
            break;
        case Screen::end:
            is_game_running = false;
            break;
        }
        return 0;
    }
}

void welcome_screen() {
    cout << "\n===|Spire Lite|===\n" << endl;
    cout << "    Main Menu   " << endl;
    cout << "   1-Start      " << endl;
    cout << "   2-Game Record" << endl;
    cout << "   3-More Info  " << endl;
    cout << "   4-Quit       " << endl;

    int choice;
    cin >> choice;
    switch(choice) {
        case 1:
            cur_screen = Screen::lobby;
            break;
        case 2:
            record_screen();
            break;
        case 3:
            info_screen();
            break;
        case 4:
            cur_screen = Screen::end;
            break;
        default:
            cout << "Invalid Choice" << endl;
            break;
    }
}    
 
void save_slot_screen() {

}

void map_screen() {
    Map map(difficulty*4+10);
    playmap(map);
}

void battle_screen() {
    cur_battle.process_player_input();
    cur_battle.print_battle_screen();
}

