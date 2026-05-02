#ifndef POTION_H
#define POTION_H

#include <string>
#include <vector>

using namespace std;

enum class PotionType {
    Heal,
    Energy,
    Fire,
    Block
};

struct Potion {
    string name;
    string description;
    PotionType type;
    int value;
    bool needs_enemy_target;

    Potion();
    Potion(string name, string description, PotionType type, int value, bool needs_enemy_target);
};

Potion create_potion(const string &name);
Potion create_random_potion();
vector<Potion> create_starting_potions();

#endif
