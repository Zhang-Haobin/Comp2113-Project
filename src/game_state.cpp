#include "../include/game_state.h"
#include "../include/Cardfactory.h"
#include <fstream>
#include <iostream>

using namespace std;

namespace {
const string map_save_marker = "MAP_V1";
}

GameState::GameState() : current_map(0) {
    score = 0;
    current_floor = 0;
    is_boss_fight = false;
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

    fout << map_save_marker << "\n";
    fout << current_map.currentLayer << " " << current_map.currentNodeIdx
         << " " << current_map.layers.size() << "\n";

    for (const vector<Node>& layer : current_map.layers) {
        fout << layer.size() << "\n";
        for (const Node& node : layer) {
            fout << static_cast<int>(node.type) << " " << node.nextIndices.size();
            for (int next_idx : node.nextIndices) {
                fout << " " << next_idx;
            }
            fout << "\n";
        }
    }

    fout.close();
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

    string marker;
    if (!(fin >> marker) || marker != map_save_marker) {
        int total_layers = player.difficulty * 4 + 10;
        current_map = Map(total_layers);
        current_map.currentLayer = current_floor;
        current_map.currentNodeIdx = 0;
        fin.close();
        return true;
    }

    int layer_count;
    fin >> current_map.currentLayer >> current_map.currentNodeIdx >> layer_count;
    current_map.layers.clear();
    current_map.layers.resize(layer_count);

    for (int i = 0; i < layer_count; i++) {
        int node_count;
        fin >> node_count;
        current_map.layers[i].resize(node_count);

        for (int j = 0; j < node_count; j++) {
            int type;
            int next_count;
            fin >> type >> next_count;
            current_map.layers[i][j].type = static_cast<NodeType>(type);
            current_map.layers[i][j].nextIndices.clear();

            for (int k = 0; k < next_count; k++) {
                int next_idx;
                fin >> next_idx;
                current_map.layers[i][j].nextIndices.push_back(next_idx);
            }
        }
    }

    fin.close();
    return true;
}

void GameState::reset() {
    player = Player();
    current_map = Map();
    score = 0;
    current_floor = 0;
    is_boss_fight = false;
}
