#ifndef ENEMY_H
#define ENMEY_H
#include <string>
using namespace std;

struct Enemy{
    string enemy_name;
    int hp;
    int max_hp;
    int attack;
    int armor;

    Enemy();
    Enemy( string enemy_name,int map_hp,int attack,int armor );

    void take_damage(int attck);   // the enemy is attacked
    int get_attack() const;        //the enemy attack player
    bool is_dead() const;


    static Enemy create_Cultist();
    static Enemy create_JawWorm();
    static Enemy create_Boss();









    
};




















#endif