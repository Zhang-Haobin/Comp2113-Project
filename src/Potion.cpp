#include "../include/Potion.h"

#include <cstdlib>
//potion 
Potion::Potion() {
    name = "Unknown Potion";
    description = "No effect.";
    type = PotionType::Heal;
    value = 0;
    needs_enemy_target = false;
}
//member function
Potion::Potion(string name, string description, PotionType type, int value, bool needs_enemy_target) {
    this->name = name;
    this->description = description;
    this->type = type;
    this->value = value;
    this->needs_enemy_target = needs_enemy_target;
}
//create potion
//you can add more if you want to extend
Potion create_potion(const string &name) {
    if(name == "Healing Potion") {
        return Potion("Healing Potion", "Heal 10 HP.", PotionType::Heal, 10, false);
    }
    if(name == "Energy Potion") {
        return Potion("Energy Potion", "Gain 2 energy this turn.", PotionType::Energy, 2, false);
    }
    if(name == "Fire Potion") {
        return Potion("Fire Potion", "Deal 12 damage to one enemy.", PotionType::Fire, 12, true);
    }
    if(name == "Block Potion") {
        return Potion("Block Potion", "Gain 8 block.", PotionType::Block, 8, false);
    }

    return Potion();
}
//random potion
Potion create_random_potion() {
    int index = rand() % 4;
    if(index == 0) return create_potion("Healing Potion");
    if(index == 1) return create_potion("Energy Potion");
    if(index == 2) return create_potion("Fire Potion");
    return create_potion("Block Potion");
}

vector<Potion> create_starting_potions() {
    vector<Potion> potions;
    potions.push_back(create_potion("Healing Potion"));
    return potions;
}
