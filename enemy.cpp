

#include <string>

#include "enemy.h"

using namespace std;

Enemy::Enemy() { //creat an object;
    enemy_name = "unknown";
    max_hp = 15;
    hp = 15;
    attack = 5;
    armor = 0;
}
//This function is to creat a enemy you want
//You can define whatever you want

Enemy::Enemy(string enemy_name, int max_hp, int attack, int armor) {
    this->enemy_name = enemy_name;
    this->max_hp = max_hp;
    this->hp = max_hp;
    this->attack = attack;
    this->armor = armor;
}

void Enemy::take_damage(int attack) {
    int real_damage = attack - armor;
    if (real_damage < 0){
        real_damage = 0;
    }
    hp -= real_damage;
    if (hp <= 0){
        hp = 0;
    }
}
int Enemy::get_attack() const {
    return attack;
}

bool Enemy::is_dead() const {
    return hp <= 0;
}

Enemy Enemy::create_Cultist() {
    return Enemy("Cultist", 20, 5, 0);
}

Enemy Enemy::create_JawWorm() {
    return Enemy("Jaw Worm", 30, 7, 0);
}

Enemy Enemy::create_Boss() {
    return Enemy("Boss", 60, 12, 0);
}
