#ifndef MAP_H
#define MAP_H

#include <vector>
#include <utility>  

// The room types that can appear on the climb map.
enum class NodeType {
    NormalEnemy,
    Event,
    Boss,
    Start
};

// A node is one room on the map. nextIndices points to rooms in the next layer.
struct Node {
    NodeType type;
    std::vector<int> nextIndices;
};

// Map stores all layers and remembers where the player is now.
class Map {
public:
    std::vector<std::vector<Node>> layers;
    int currentLayer;
    int currentNodeIdx;

    // Create a map with a number of layers. Zero layers is allowed for an empty save object.
    Map(int numLayers = 0);

    // Fill all layers with random rooms and random connections.
    void generate();

    // Current room, used after the player chooses where to go.
    Node& getCurrentNode();

    // List rooms reachable from the current room.
    std::vector<std::pair<int, NodeType>> getNextNodes();

    // Move to one of the reachable rooms if the chosen node is valid.
    bool moveToNextLayer(int nextNodeIdx);

    // True when the current layer is the final boss layer.
    bool isBossLayer();

    
};

// Turns the enum into readable text for the terminal.
void displayNodeType(NodeType type);

// Show the map choices and let the player pick the next room.
void playmap(Map &map);

#endif 
