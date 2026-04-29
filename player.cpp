#include "player.h"

int Player::get_hp_after_heal(int hp_add) {
	hp += hp_add;
	if (hp > max_hp) {
		hp = max_hp;
	}
	return hp;
}

int Player::get_hp_after_hurt(int hp_minus) {
	hp -= hp_minus;
	if (hp < 0) {
		hp = 0;
	}
	return hp;
}

int Player::get_damage(int atk) {
	return (atk + damage_boost) * strength;
}
