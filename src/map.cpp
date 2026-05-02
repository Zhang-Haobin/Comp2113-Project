#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "../include/map.h"
#include "../include/main.h"

using namespace std;

Map::Map(int numLayers) {                             
        layers.resize(numLayers);
        currentLayer = 0;
        generate();
    }

void Map::generate() {
        for (size_t i = 0; i < layers.size(); ++i) { 
            if (i == 0) {                                        //first layer, only start node
                layers[i].resize(1);
                layers[i][0].type = NodeType::Start;
                continue;
            }
            if (i == layers.size() - 1) {                        //last layer, only boss node
                layers[i].resize(1);
                layers[i][0].type = NodeType::Boss;
                continue;
            }

            int nodeCount = 3 + rand() % 3;                      //middle Layers have 3-5 nodes
            layers[i].resize(nodeCount);
            for (int j = 0; j < nodeCount; ++j) {
                int r = rand() % 100;
                if (r < 60) {
                    layers[i][j].type = NodeType::NormalEnemy;           // 60% chance for normal enemy
                }else{
                    layers[i][j].type = NodeType::Event;                 // 40% chance for event
                }
            }
        }

     
        for (size_t i = 0; i < layers.size() - 1; ++i) {                       // Connect Layer i to Layer i+1
            for (size_t j = 0; j < layers[i].size(); ++j) {
                int maxConnection = (i == 0) ? 2 : (1 + rand() % 2);                  //the each nodes can have up to 2 connections
                int nextLayerSize = static_cast<int>(layers[i+1].size());      
                for (int k = 0; k < maxConnection; ++k) {                          
                    int targetIdx = rand() % nextLayerSize;
                   
                    bool exists = false;
                    for (int idx : layers[i][j].nextIndices) {
                        if (idx == targetIdx) { exists = true; break; }
                    }
                    if (!exists) {
                        layers[i][j].nextIndices.push_back(targetIdx);
                    }
                }
            }  
        }

        for (size_t i = 1; i < layers.size(); ++i) {                        //Check if each node in layer i has at least one parent in layer i-1, if not, connect it to a random node in layer i-1
            for (size_t j = 0; j < layers[i].size(); ++j) {
                if (i == layers.size() - 1) continue; 
                bool hasParent = false;
                for (size_t pi = 0; pi < layers[i-1].size(); ++pi) {
                    for (int idx : layers[i-1][pi].nextIndices) {
                        if (idx == static_cast<int>(j)) {
                            hasParent = true;
                            break;
                        }
                    }
                    if (hasParent) break;
                }
                if (!hasParent) {
                    int srcIdx = rand() % layers[i-1].size();
                    layers[i-1][srcIdx].nextIndices.push_back(static_cast<int>(j));
                }
            }
        }

        currentNodeIdx = 0;
    }

    Node& Map::getCurrentNode() {
        return layers[currentLayer][currentNodeIdx];
    }

    vector<pair<int, NodeType>> Map::getNextNodes() {
        vector<pair<int, NodeType>> result;
        if (currentLayer + 1 >= static_cast<int>(layers.size())) return result;
        for (int idx : getCurrentNode().nextIndices) {
            if (idx < static_cast<int>(layers[currentLayer+1].size())) {
                result.emplace_back(idx, layers[currentLayer+1][idx].type);
            }
        }
        return result;
    }

    bool Map::moveToNextLayer(int nextNodeIdx) {
        auto nexts = getNextNodes();
        bool valid = false;
        for (auto& p : nexts) {
            if (p.first == nextNodeIdx) { valid = true; break; }
        }
        if (!valid) return false;
        currentLayer++;
        currentNodeIdx = nextNodeIdx;
        return true;
    }

    bool Map::isBossLayer() {
        return currentLayer == static_cast<int>(layers.size()) - 1;
    }

void displayNodeType(NodeType type) {
    switch (type) {
        case NodeType::NormalEnemy: std::cout << "Normal Enemy"; break;
        case NodeType::Event:       std::cout << "Event"; break;
        case NodeType::Boss:        std::cout << "BOSS"; break;
        case NodeType::Start:       std::cout << "Starting Point"; break;
    }
} 
void playmap(Map &map){
    while (!map.isBossLayer()) {
        
        Node& cur = map.getCurrentNode();                                          //show the current stages
        cout << "=== Map ===\n\n";
        cout << "Current stage: " << map.currentLayer << "\n";
        cout << "Current node: ";
        displayNodeType(cur.type);
        cout << "\n";

        auto nexts = map.getNextNodes();

        cout << "\nChoose your next path:\n";                                                //show reachable node
        for (size_t i = 0; i < nexts.size(); ++i) {
            cout << "  [" << (i + 1) << "] ";
            displayNodeType(nexts[i].second);
            if (nexts[i].second == NodeType::NormalEnemy) {
                cout << " - fight an enemy and earn a card reward";
            }
            else if (nexts[i].second == NodeType::Event) {
                cout << " - advance through a story event";
            }
            else if (nexts[i].second == NodeType::Boss) {
                cout << " - final boss battle";
            }
            cout << "\n";
        }

        cout << "\nEnter path number (1-" << nexts.size() << "): ";
        int choice = read_int();

        if (1 <= choice && choice <= static_cast<int>(nexts.size())) {                                 //choose one node to move
            int targetIdx = nexts[choice - 1].first;
            if (map.moveToNextLayer(targetIdx)) {
                return;
            }
        }
        else {
            cout << "Invalid path. Choose one of the listed numbers.\n";
        } 
    }
}
