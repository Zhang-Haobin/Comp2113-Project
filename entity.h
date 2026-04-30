#ifndef ENTITY_H
#define ENTITY_H

class Entity {
private:
    int max_hp = 0;
    int hp = 0;
    int strength = 1;         // damage multiplier
    int damage_boost = 0;     // damage boost
    int block = 0;            // damage reduction
    // todo...

public:
    Entity() = default;
    Entity(int max_hp) : max_hp(max_hp), hp(max_hp) {}

    int get_hp() const { return hp; }
    int get_max_hp() const { return max_hp; }
    int get_strength() const { return strength; }
    int get_damage_boost() const { return damage_boost; }
    int get_block() const { return block; }

    void set_hp(int new_hp) {
        hp = new_hp;
        if(hp > max_hp) {
            hp = max_hp;
        }
        else if(hp < 0) {
            hp = 0;
        }
    }
    void set_strength(int new_strength) {
        strength = new_strength;
    }
    void set_damage_boost(int new_damage_boost) {
        damage_boost = new_damage_boost;
    }
    void set_block(int new_block) {
        block = new_block;
    }
};

#endif // ifndef ENTITY_H
