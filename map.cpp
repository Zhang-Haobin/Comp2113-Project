#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

enum class NodeType { NormalEnemy, EliteEnemy, Shop, Campfire, Event, Boss, Start };

struct Node {
    NodeType type;
    vector<int> nextIndices;   
};


class Map {
public:
    vector<vector<Node>> layers;
    int currentLayer;     
    int currentNodeIdx;   

    Map(int numLayers = 5) {                             
        layers.resize(numLayers);
        currentLayer = 0;
        generate();
    }

    void generate() {
        srand(static_cast<unsigned> (time(nullptr)));            //random seed

    
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
                int maxConnection = (i == 0) ? 2 : (1 + rand() % 2);                  //the first layer can have up to 2 connections, the others can have 1-2 connections
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

    Node& getCurrentNode() {
        return layers[currentLayer][currentNodeIdx];
    }

    vector<pair<int, NodeType>> getNextNodes() {
        vector<pair<int, NodeType>> result;
        if (currentLayer + 1 >= static_cast<int>(layers.size())) return result;
        for (int idx : getCurrentNode().nextIndices) {
            if (idx < static_cast<int>(layers[currentLayer+1].size())) {
                result.emplace_back(idx, layers[currentLayer+1][idx].type);
            }
        }
        return result;
    }

    bool moveToNextLayer(int nextNodeIdx) {
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

    bool isBossLayer() {
        return currentLayer == static_cast<int>(layers.size()) - 1;
    }
};

void displayNodeType(NodeType type) {
    switch (type) {
        case NodeType::NormalEnemy: std::cout << "Normal Enemy"; break;
        case NodeType::Event:       std::cout << "Event"; break;
        case NodeType::Boss:        std::cout << "BOSS"; break;
        case NodeType::Start:       std::cout << "Starting Point"; break;
    }
}

//this function↓ is only used for testing the random system. will not be contained in final code (We will make it be showed by the map_screen)
void playMap() {
    Map map(5);

    while (!map.isBossLayer()) {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; 
       

        Node& cur = map.getCurrentNode();
        cout << "=== Current Stage ===" << endl;
        cout << "           " << map.currentLayer << endl;
        displayNodeType(cur.type);
        cout << "\n\n";

        auto nexts = map.getNextNodes();

        cout<<"Reachable Nodes:"<<endl;
        for (size_t i = 0; i < nexts.size(); ++i) {
            cout << "  " << (i + 1) << ". ";
            displayNodeType(nexts[i].second);
            cout << "\n";
        }

        cout << "\nEnter (1-" << nexts.size() << ") to move or enter 0 to pause: ";
        int choice;
        cin >> choice;

        if (choice == 0) {
            cout <<" Game Paused "<< endl;

            return;
        }

        if (choice >= 1 && choice <= static_cast<int>(nexts.size())) {
            int targetIdx = nexts[choice - 1].first;
            if (map.moveToNextLayer(targetIdx)) {
                continue; 
            }
        }

        cout << "Invalid choice\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }

    
   cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
   cout << "=== Final Stage ===\n";
   displayNodeType(map.getCurrentNode().type);
   cout << "\n";
   cout << "Press enter to continue...";
   cin.ignore();
   cin.get();
}
