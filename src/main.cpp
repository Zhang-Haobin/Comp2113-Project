#include "../include/main.h"
#include "../include/player.h"
#include "../include/save.h"
#include "../include/battle.h"
#include "../include/map.h"
#include "../include/Cardfactory.h"
#include "../include/Deck.h"
#include "../include/Potion.h"
#include "../include/enemy.h"
#include "../include/game_state.h"
#include "../include/event_screen.h"
#include "../include/difficulty.h"

#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstdio>
#include <chrono>
#include <thread>

using namespace std;

bool is_game_running = true;
int difficulty = 2;
int current_score = 0;
bool current_run_won = false;
bool record_saved = false;
Screen cur_screen = Screen::welcome;
Battle cur_battle;
Map cur_map;
const string game_save_file = "game_save.txt";

namespace {
bool keep_next_welcome_screen = false;

// Small helper so all menus print options in the same style.
void print_menu_option(int option, const string &label, const string &detail) {
    cout << option << ". " << label;
    if(!detail.empty()) {
        cout << " - " << detail;
    }
    cout << "\n";
}

// Continue is only available if the current-run save exists.
bool saved_game_exists() {
    ifstream fin(game_save_file);
    return fin.good();
}

// Difficulty controls how long the climb is.
int total_map_layers_for_difficulty(int difficulty_level) {
    return get_difficulty_by_level(difficulty_level).map_layers;
}

// Apply the chosen difficulty to enemy stats after an enemy template is created.
Enemy scale_enemy_for_difficulty(Enemy enemy, int difficulty_level) {
    DifficultySettings settings = get_difficulty_by_level(difficulty_level);
    enemy.max_hp = max(1, static_cast<int>(enemy.max_hp * settings.enemy_hp_multiplier + 0.5f));
    enemy.hp = enemy.max_hp;
    enemy.base_attack = max(1, static_cast<int>(enemy.base_attack * settings.enemy_damage_multiplier + 0.5f));
    enemy.attack = enemy.base_attack;
    return enemy;
}

bool should_add_second_enemy(int difficulty_level, int stage) {
    if(difficulty_level == 2 && stage >= 5) {
        return rand() % 100 < 20;
    }
    if(difficulty_level == 3 && stage >= 3) {
        return rand() % 100 < 30;
    }
    return false;
}

void try_give_map_potion(Player &player, int chance_percent) {
    if(static_cast<int>(player.potions.size()) >= player.max_potion) {
        return;
    }
    if(rand() % 100 >= chance_percent) {
        return;
    }

    Potion potion = create_random_potion();
    player.potions.push_back(potion);
    cout << "You found a " << potion.name << ".\n";
}

// New run gets a fresh generated map.
void reset_current_map_for_player() {
    cur_map = Map(total_map_layers_for_difficulty(cur_battle.player.difficulty));
}

// If loading an old/broken save, rebuild enough map data so the run can continue.
void ensure_current_map_ready() {
    int total_layers = total_map_layers_for_difficulty(cur_battle.player.difficulty);
    if(cur_map.layers.empty() || static_cast<int>(cur_map.layers.size()) != total_layers) {
        cur_map = Map(total_layers);
        cur_map.currentLayer = min(cur_battle.player.stage, total_layers - 1);
        cur_map.currentNodeIdx = 0;
    }
    cur_map.currentLayer = max(0, min(cur_map.currentLayer, total_layers - 1));
    if(cur_map.layers[cur_map.currentLayer].empty()
       || cur_map.currentNodeIdx < 0
       || cur_map.currentNodeIdx >= static_cast<int>(cur_map.layers[cur_map.currentLayer].size())) {
        cur_map.currentNodeIdx = 0;
    }
}

void print_startup_splash() {
    print_sep_line();
    cout << "\033[33m" << R"(


      ███████╗██╗      █████╗ ██╗   ██╗    ████████╗██╗  ██╗███████╗
      ██╔════╝██║     ██╔══██╗╚██╗ ██╔╝    ╚══██╔══╝██║  ██║██╔════╝
      ███████╗██║     ███████║ ╚████╔╝        ██║   ███████║█████╗
      ╚════██║██║     ██╔══██║  ╚██╔╝         ██║   ██╔══██║██╔══╝
      ███████║███████╗██║  ██║   ██║          ██║   ██║  ██║███████╗
      ╚══════╝╚══════╝╚═╝  ╚═╝   ╚═╝          ╚═╝   ╚═╝  ╚═╝╚══════╝

        ███████╗██████╗ ██╗██████╗ ███████╗    ██╗     ██╗████████╗███████╗
        ██╔════╝██╔══██╗██║██╔══██╗██╔════╝    ██║     ██║╚══██╔══╝██╔════╝
        ███████╗██████╔╝██║██████╔╝█████╗      ██║     ██║   ██║   █████╗
        ╚════██║██╔═══╝ ██║██╔══██╗██╔══╝      ██║     ██║   ██║   ██╔══╝
        ███████║██║     ██║██║  ██║███████╗    ███████╗██║   ██║   ███████╗
        ╚══════╝╚═╝     ╚═╝╚═╝  ╚═╝╚══════╝    ╚══════╝╚═╝   ╚═╝   ╚══════╝

)" << "\033[36m" << R"(
        ---------------------------------------------------------------------
                  A tiny text-based deckbuilding climb
        ---------------------------------------------------------------------

)" << "\033[0m" << flush;
    this_thread::sleep_for(chrono::milliseconds(2300));
    print_sep_line();
}
}

int main() {
    // Initialize random seed for enemy/card generation
    srand(time(0));
    print_startup_splash();
    keep_next_welcome_screen = true;
    
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
    if(keep_next_welcome_screen) {
        keep_next_welcome_screen = false;
        cout << "\n";
    }
    else {
        print_sep_line();
    }
    record record = get_record();
    cout << "==== Spire Lite ====\n";
    cout << "A tiny text-based deckbuilding climb.\n";
    cout << "Best stage: " << record.highest_floor
         << " | Wins: " << record.total_wins
         << " | Losses: " << record.total_losses << "\n\n";
    print_menu_option(1, "Start run", "");
    print_menu_option(2, "Continue save", "");
    print_menu_option(3, "Game record", "");
    print_menu_option(4, "How to play", "");
    print_menu_option(5, "Card library", "");
    print_menu_option(6, "Quit", "");
    cout << "Choose: ";

    int choice = read_int();
    switch(choice) {
        case 1:
            cur_screen = Screen::lobby;
            break;
        case 2:
            if(load_current_game()) {
                cout << "\nLoaded saved run for " << cur_battle.player.name << ".\n";
                cur_screen = Screen::map;
            }
            else {
                cout << "\nNo saved game found.\n";
            }
            break;
        case 3:
            record_screen();
            break;
        case 4:
            info_screen();
            break;
        case 5:
            card_library_screen();
            break;
        case 6:
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
    cout << "==== Start Run ====\n";
    cout << "Save file: ";
    if(saved_game_exists()) {
        cout << "found\n\n";
    }
    else {
        cout << "none\n\n";
    }

    print_menu_option(1, "New run", "fresh character and starter deck");
    print_menu_option(2, "Back", "return to main menu");
    cout << "Choose: ";

    int option = read_int();
    switch(option) {
    case 1: {
        // Get player name and create new battle
        string new_name;
        cout << "\nEnter player name: ";
        cin >> new_name;
        
        int selected_difficulty = 0;
        while(selected_difficulty < 1 || selected_difficulty > 3) {
            print_difficulty_options();
            selected_difficulty = read_int();
            if(selected_difficulty < 1 || selected_difficulty > 3) {
                cout << "Invalid difficulty. Choose 1, 2, or 3.\n";
            }
        }
        difficulty = selected_difficulty;

        // Initialize battle with new player
        cur_battle = Battle();
        cur_battle.player.name = new_name;
        cur_battle.player.cards = Cardfactory::create_starter_carddeck();  // Initialize player deck with starter cards
        cur_battle.player.potions = create_starting_potions();
        cur_battle.player.stage = 0;
        apply_difficulty_to_player(difficulty, cur_battle.player);
        reset_current_map_for_player();
        current_score = get_difficulty_by_level(difficulty).starting_bonus;
        current_run_won = false;
        record_saved = false;
        save_current_game();
        
        cout << "\nNew run created. Welcome to Spire Lite, " << new_name << ".\n";
        cur_screen = Screen::map;
        break;
    }
    case 2: {
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
    ensure_current_map_ready();
    playmap(cur_map);

    Node& newNode = cur_map.getCurrentNode(); 
    switch(newNode.type) {
        case NodeType::NormalEnemy: {
            // Generate enemy for this normal enemy encounter
            cur_battle.enemies.clear();  // Clear any previous enemies
            Enemy enemy = create_normal_enemy_by_floor(cur_battle.player.stage);  // Generate enemy based on current stage
            enemy = scale_enemy_for_difficulty(enemy, cur_battle.player.difficulty);
            cur_battle.enemies.push_back(enemy);
            if(should_add_second_enemy(cur_battle.player.difficulty, cur_battle.player.stage)) {
                Enemy second_enemy = create_normal_enemy_by_floor(cur_battle.player.stage);
                second_enemy = scale_enemy_for_difficulty(second_enemy, cur_battle.player.difficulty);
                cur_battle.enemies.push_back(second_enemy);
            }
            cur_battle.start_combat(false);
            
            cout << "\nEncounter started:";
            for(const Enemy &battle_enemy : cur_battle.enemies) {
                cout << " " << battle_enemy.name;
            }
            cout << ".\n";
            cur_screen = Screen::battle;  // Jump to the battle screen
            break;
        }
        case NodeType::Event: {
            trigger_random_event(cur_battle.player, current_score);
            if(cur_battle.player.is_dead()) {
                current_run_won = false;
                record_current_run();
                cur_screen = Screen::end;
                break;
            }

            cur_battle.player.stage++;
            try_give_map_potion(cur_battle.player, 15);
            save_current_game();
            cur_screen = Screen::map;
            break;
        }
        case NodeType::Boss: {
            cur_battle.enemies.clear();
            Enemy boss = create_boss_enemy();
            boss = scale_enemy_for_difficulty(boss, cur_battle.player.difficulty);
            cur_battle.enemies.push_back(boss);
            cur_battle.start_combat(true);

            cout << "\nBoss encounter started: " << boss.name << ".\n";
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
    if(cur_battle.keep_next_battle_screen) {
        cur_battle.keep_next_battle_screen = false;
        cout << "\n";
    }
    else {
        print_sep_line();
    }
    cur_battle.print_battle_screen();  // Display current battle state
    cur_battle.process_player_input();  // Get and process player action
}

// Display end game screen with results
void end_screen() {
    print_sep_line();
    cout << "==== Run Result ====\n";
    if(current_run_won) {
        cout << "You cleared the spire. Victory!\n";
    }
    else {
        cout << "The climb ends here.\n";
    }
    cout << "Player: " << cur_battle.player.name
         << " | Score: " << current_score
         << " | Stage: " << cur_battle.player.stage << "\n\n";

    print_menu_option(1, "Main menu", "");
    print_menu_option(2, "Quit", "");
    cout << "Choose: ";

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
    cout << "\n";
    print_menu_option(1, "Back", "return to main menu");
    print_menu_option(2, "Reset record", "clear best score and win/loss record");
    cout << "Choose: ";

    int choice = read_int();
    if(choice == 2) {
        record empty_record;
        empty_record.reset_record();
        save_record(empty_record);
        cout << "Game record reset.\n";
    }
    else if(choice != 1) {
        cout << "Invalid option!\n";
    }

    keep_next_welcome_screen = true;
    cur_screen = Screen::welcome;
}

// Display every card template in the game.
void card_library_screen() {
    vector<string> card_names = Cardfactory::getall_cardnames();
    int card_count = static_cast<int>(card_names.size());
    Card* cards = new Card[card_count];

    for(int i = 0; i < card_count; i++) {
        cards[i] = Cardfactory::create_card(card_names[i]);
    }

    cout << "==== Card Library ====\n";
    for(int i = 0; i < card_count; i++) {
        cout << i + 1 << ". " << cards[i].getName() << endl;
    }

    cout << "\nDetails:\n";
    for(int i = 0; i < card_count; i++) {
        cout << "[" << cards[i].getType() << "] "
             << cards[i].getName()
             << " (" << cards[i].getCost() << ") - "
             << cards[i].getDescription() << "\n";
    }

    delete[] cards;

    keep_next_welcome_screen = true;
    cur_screen = Screen::welcome;
}

// Display game information
void info_screen() {
    cout << "==== How To Play ====\n";
    cout << "Map: choose a reachable node number to move to the next stage.\n";
    cout << "Battle: choose card numbers from your hand. Attack cards ask for a target.\n";
    cout << "Turn flow: play any cards you can afford, then choose End turn.\n";
    cout << "Cards: your deck is permanent; each battle uses draw and discard piles.\n";
    cout << "Goal: survive the map and defeat the boss.\n";
    keep_next_welcome_screen = true;
    cur_screen = Screen::welcome;
}

// Save the current run, including the map.
void save_current_game() {
    GameState state;
    state.player = cur_battle.player;
    state.current_map = cur_map;
    state.score = current_score;
    state.current_floor = cur_map.currentLayer;
    state.save_to_file(game_save_file);
}

// Load a run and clear any old in-combat piles.
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
    cur_map = state.current_map;
    ensure_current_map_ready();
    current_score = state.score;
    current_run_won = false;
    record_saved = false;
    return true;
}

// Record the finished run once, then remove the current-run save.
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

// Clear the terminal before drawing a new screen.
void print_sep_line() {
    cout << "\033[2J\033[H";
}
