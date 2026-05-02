#ifndef ENTITY_H
#define ENTITY_H

// A generic base-style entity for HP/block/strength experiments.
// Player and Enemy ended up using their own simpler structs, but this still supports effect.cpp.
class Entity {
private:
    int max_hp = 0;
    int hp = 0;
    int strength = 1;         // damage multiplier
    int damage_boost = 0;     // damage boost
    int block = 0;            // damage reduction
    // todo...

public:
    // Empty entity, mostly for default construction.
    Entity() = default;

    // Create something with full HP.
    Entity(int max_hp) : max_hp(max_hp), hp(max_hp) {}

    // Basic readers.
    int get_hp() const { return hp; }
    int get_max_hp() const { return max_hp; }
    int get_strength() const { return strength; }
    int get_damage_boost() const { return damage_boost; }
    int get_block() const { return block; }

    // HP setter clamps the value because negative HP or overheal is annoying elsewhere.
    void set_hp(int new_hp) {
        hp = new_hp;
        if(hp > max_hp) {
            hp = max_hp;
        }
        else if(hp < 0) {
            hp = 0;
        }
    }
    // These setters are plain because the battle code decides the real rules.
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
