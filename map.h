#ifndef MAP_H
#define MAP_H

#include <vector>
#include <utility>  

enum class NodeType {
    NormalEnemy,
    Event,
    Boss,
    Start
};

struct Node {
    NodeType type;
    std::vector<int> nextIndices;
};

class Map {
public:
    std::vector<std::vector<Node>> layers;
    int currentLayer;
    int currentNodeIdx;

    Map(int numLayers = 5);

    void generate();

    Node& getCurrentNode();

    std::vector<std::pair<int, NodeType>> getNextNodes();

    bool moveToNextLayer(int nextNodeIdx);

    bool isBossLayer();

    
};

void displayNodeType(NodeType type);

void playmap(Map &map)

#endif 
