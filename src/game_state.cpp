#include "../include/game_state.h"
#include "../include/Cardfactory.h"
#include <fstream>
#include <iostream>

using namespace std;

GameState::GameState() {
    current_map = nullptr;
    score = 0;
    current_floor = 0;
    is_boss_fight = false;
}

GameState::~GameState() {
    if (current_map != nullptr) delete current_map;
}

void GameState::save_to_file(const string& filename) {
    ofstream fout(filename);
    if (!fout) return;
    
    fout << player.name << "\n";
    fout << player.max_hp << " " << player.hp << "\n";
    fout << player.max_energy << " " << player.energy << "\n";
    fout << player.strength << " " << player.damage_boost << " " << player.block << "\n";
    fout << player.stage << " " << player.difficulty << "\n";
    fout << player.max_card << "\n";
    fout << player.cards.size() << "\n";
    
    for (const Card& card : player.cards) {
        fout << card.getName() << "\n";
    }
    
    fout << score << "\n" << current_floor << "\n" << is_boss_fight << "\n";
    fout.close();
    cout << "Game saved.\n";
}

bool GameState::load_from_file(const string& filename) {
    ifstream fin(filename);
    if (!fin) return false;
    
    player.cards.clear();
    
    getline(fin, player.name);
    fin >> player.max_hp >> player.hp;
    fin >> player.max_energy >> player.energy;
    fin >> player.strength >> player.damage_boost >> player.block;
    fin >> player.stage >> player.difficulty;
    fin >> player.max_card;
    
    int deck_size;
    fin >> deck_size;
    fin.ignore();
    
    for (int i = 0; i < deck_size; i++) {
        string card_name;
        getline(fin, card_name);
        player.cards.push_back(Cardfactory::create_card(card_name));
    }
    
    fin >> score >> current_floor >> is_boss_fight;
    fin.close();
    cout << "Game loaded.\n";
    return true;
}

void GameState::reset() {
    if (current_map != nullptr) {
        delete current_map;
        current_map = nullptr;
    }
    player = Player();
    score = 0;
    current_floor = 0;
    is_boss_fight = false;
}