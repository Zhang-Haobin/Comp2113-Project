#ifndef ENEMY_H
#define ENEMY_H
#include <string>
using namespace std;

struct Enemy{
    static Enemy create_Cultist();
    static Enemy create_JawWorm();
    static Enemy create_Boss();

    string name;
    int hp;
    int max_hp;
    int attack;
    int armor;

    Enemy();
    Enemy(string name, int max_hp, int attack, int armor);

    void take_damage(int attck);   // the enemy is attacked
    int get_attack() const;        //the enemy attack player
    bool is_dead() const;
};

#endif // ifndef ENEMY_H
