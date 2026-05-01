#include "../include/main.h"
#include "../include/player.h"
#include "../include/save.h"
#include "../include/battle.h"
#include "../include/map.h"

#include <iostream>
#include <string>
#include <limits>

using namespace std;

bool is_game_running = true;
int difficulty = 2;
Screen cur_screen = Screen::welcome;
Battle cur_battle;

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
        case Screen::end:
            end_screen();
            break;
        case Screen::quit:
            is_game_running = false;
            break;
        default:
            cout << "Unimplemented screen!\n";
            break;
        }
        
    }
    return 0;
}

int read_int() { // read until input is really integer
    int input;
    cin >> input;
    while(cin.fail()) {
        cout << "Invalid input!\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> input;
    }
    return input;
}

void welcome_screen() {
    cout << "\n===|Spire Lite|===\n" << endl;
    cout << "    Main Menu   " << endl;
    cout << "   1. Start      " << endl;
    cout << "   2. Game Record" << endl;
    cout << "   3. More Info  " << endl;
    cout << "   4. Quit       " << endl;

    int choice = read_int();
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
            cur_screen = Screen::quit;
            break;
        default:
            cout << "Invalid Choice" << endl;
            break;
    }
}    
 
void save_slot_screen() {
    cout << " Saves:\n";
    cout << "1. New Game\n";
    cout << "2. Browse Saves\n";
    cout << "3. Main Menu\n";

    int option = read_int();
    switch(option) {
    case 1: {
        string new_name;
        cout << "Type your name: ";
        cin >> new_name;
        Player player;
        player.name = new_name;
        cout << "\nCreate successfully, welcome to Spire Lite, " << new_name << endl;
        //todo: insert a difficulty selection function and store it in player.difficulty
        cur_screen = Screen::map;
        break;
    }
    case 2: {
        // todo
        break;
    }
    case 3: {
        cur_screen = Screen::welcome;
        break;
    }
    default: {
        cout << "Invalid option!\n";
        break;
    }
    }
}

void map_screen() {
    Map map((cur_battle.player.difficulty) * 4 + 10);
    playmap(map);
    Node& newNode = map.getCurrentNode(); 
    switch(newNode.type) {
        case NodeType::NormalEnemy:
            cur_screen = Screen::battle; // jump to the battle screen
            break;
        case NodeType::Event: // todo: we need to add some random events here
            break;         
    }
}

void battle_screen() {
    cur_battle.process_player_input();
    cur_battle.print_battle_screen();
}

void end_screen() {
    cout << "Rest In Peace, " << cur_battle.player.name << "\n\n";
    cout << "Difficulty: " << cur_battle.player.difficulty << "\n";
    cout << "Stage: " << cur_battle.player.stage << "\n\n";

    cout << "1. Main Menu\n\n";
    cout << "2. Quit\n\n";

    int option = read_int();
    switch(option) {
    case 1: {
        cur_screen = Screen::welcome;
        break;
    }
    case 2: {
        cur_screen = Screen::quit;
        break;
    }
    default: {
        cout << "Invalid option!\n";
        break;
    }
    }
}

void lobby_screen() {
    save_slot_screen();
}

void record_screen() {
    print_record();
    cur_screen = Screen::welcome;
}

void info_screen() {
    cout << "Spire Lite" << endl;
    cur_screen = Screen::welcome;
}
