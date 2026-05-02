#ifndef ENEMY_H
#define ENEMY_H

#include <string>

using namespace std;

// Enemy is kept simple: HP, attack, armor, and a few ready-made enemy types.
struct Enemy{
    
    string name;
    int hp;
    int max_hp;
    int attack;
    int armor;

    // A tiny default enemy, mainly so vectors/classes can create one safely.
    Enemy();

    // Build a specific enemy with its battle stats.
    Enemy(string name, int max_hp, int attack, int armor);

    void take_damage(int attck);   // damage first goes through armor
    int get_attack() const;        // return the enemy's planned attack
    bool is_dead() const;

    // These static functions are the enemy templates used by the map/battle flow.
    static Enemy create_Cultist();

    static Enemy create_JawWorm();

    static Enemy create_Louses();

    static Enemy create_Slime();

    static Enemy create_Sentry();

    static Enemy create_GremlinNob();

    static Enemy create_Boss();

};

// Pick a normal enemy based on how far the player has climbed.
Enemy create_normal_enemy_by_floor(int floor);

// Final boss helper, kept separate because the map asks for it directly.
Enemy create_boss_enemy();

#endif 
