#include "../include/main.h"
#include "../include/player.h"
#include "../include/save.h"
#include "../include/battle.h"
#include "../include/map.h"
#include "../include/Cardfactory.h"
#include "../include/enemy.h"
#include "../include/game_state.h"

#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstdio>

using namespace std;

bool is_game_running = true;
int difficulty = 2;
int current_score = 0;
bool current_run_won = false;
bool record_saved = false;
Screen cur_screen = Screen::welcome;
Battle cur_battle;
const string game_save_file = "game_save.txt";

int main() {
    // Initialize random seed for enemy/card generation
    srand(time(0));
    
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

// Display welcome screen and handle main menu choices
void welcome_screen() {
    print_sep_line();
    cout << "===|Spire Lite|===\n" << endl;
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
 
// Handle save slot selection and new game creation
void save_slot_screen() {
    print_sep_line();
    cout << "    Saves:\n";
    cout << "   1. New Game\n";
    cout << "   2. Browse Saves\n";
    cout << "   3. Main Menu\n";

    int option = read_int();
    switch(option) {
    case 1: {
        // Get player name and create new battle
        string new_name;
        cout << "Type your name: ";
        cin >> new_name;
        
        // Initialize battle with new player
        cur_battle = Battle();
        cur_battle.player.name = new_name;
        cur_battle.player.cards = Cardfactory::create_starter_carddeck();  // Initialize player deck with starter cards
        cur_battle.player.stage = 0;
        cur_battle.player.difficulty = difficulty;
        current_score = 0;
        current_run_won = false;
        record_saved = false;
        save_current_game();
        
        cout << "\nCreate successfully, welcome to Spire Lite, " << new_name << endl;
        //todo: insert a difficulty selection function and store it in player.difficulty
        cur_screen = Screen::map;
        break;
    }
    case 2: {
        if(load_current_game()) {
            cout << "\nLoaded save for " << cur_battle.player.name << ".\n";
            cur_screen = Screen::map;
        }
        else {
            cout << "\nNo saved game found.\n";
        }
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

// Generate map and handle navigation to next node
void map_screen() {
    print_sep_line();
    int total_layers = (cur_battle.player.difficulty) * 4 + 10;
    Map map(total_layers);
    map.currentLayer = min(cur_battle.player.stage, total_layers - 1);
    map.currentNodeIdx = 0;
    playmap(map);

    Node& newNode = map.getCurrentNode(); 
    switch(newNode.type) {
        case NodeType::NormalEnemy: {
            // Generate enemy for this normal enemy encounter
            cur_battle.enemies.clear();  // Clear any previous enemies
            Enemy enemy = create_normal_enemy_by_floor(cur_battle.player.stage);  // Generate enemy based on current stage
            cur_battle.enemies.push_back(enemy);
            cur_battle.start_combat(false);
            
            cout << "\nA wild " << enemy.name << " appears!\n";
            cur_screen = Screen::battle;  // Jump to the battle screen
            break;
        }
        case NodeType::Event: {
            cout << "\nA quiet event passes by. You move on.\n";
            cur_battle.player.stage++;
            save_current_game();
            cur_screen = Screen::map;
            break;
        }
        case NodeType::Boss: {
            cur_battle.enemies.clear();
            Enemy boss = create_boss_enemy();
            cur_battle.enemies.push_back(boss);
            cur_battle.start_combat(true);

            cout << "\nThe boss " << boss.name << " blocks your path!\n";
            cur_screen = Screen::battle;
            break;
        }
        default:
            cout << "Unimplemented node type!\n";
            break;
    }
}

// Display battle screen and process player turn
void battle_screen() {
    print_sep_line();
    cur_battle.print_battle_screen();  // Display current battle state
    cur_battle.process_player_input();  // Get and process player action
}

// Display end game screen with results
void end_screen() {
    print_sep_line();
    if(current_run_won) {
        cout << "   Victory, " << cur_battle.player.name << "!\n\n";
    }
    else {
        cout << "   Rest In Peace, " << cur_battle.player.name << "\n\n";
    }
    cout << "   Score: " << current_score << "\n";
    cout << "   Difficulty: " << cur_battle.player.difficulty << "\n";
    cout << "   Stage: " << cur_battle.player.stage << "\n\n";

    cout << "   1. Main Menu\n\n";
    cout << "   2. Quit\n\n";

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

// Transition to save slot screen (lobby)
void lobby_screen() {
    save_slot_screen();
}

// Display game record/statistics
void record_screen() {
    print_record();
    cur_screen = Screen::welcome;
}

// Display game information
void info_screen() {
    print_sep_line();
    cout << "   Spire Lite" << endl;
    cur_screen = Screen::welcome;
}

void save_current_game() {
    GameState state;
    state.player = cur_battle.player;
    state.score = current_score;
    state.current_floor = cur_battle.player.stage;
    state.save_to_file(game_save_file);
}

bool load_current_game() {
    GameState state;
    if(!state.load_from_file(game_save_file)) {
        return false;
    }

    cur_battle = Battle();
    cur_battle.player = state.player;
    cur_battle.player.hand.clear();
    cur_battle.player.draw_pile.clear();
    cur_battle.player.discard_pile.clear();
    current_score = state.score;
    current_run_won = false;
    record_saved = false;
    return true;
}

void record_current_run() {
    if(record_saved) {
        return;
    }

    update_record(current_score, cur_battle.player.stage, current_run_won);
    record_saved = true;
    remove(game_save_file.c_str());
}

// Read integer input with validation - keeps reading until valid integer is entered
int read_int() {
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

// Print separator line for visual clarity
void print_sep_line() {
    cout << "\n------------------------------------------------------------\n\n";
}
