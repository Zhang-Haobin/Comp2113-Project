#include "player.h"

void Player::heal(const int delta) {
	hp += delta;
	if (hp > max_hp) {
		hp = max_hp;
	}
}

void Player::hurt(const int delta) {
	hp -= delta;
	if (hp < 0) {
		hp = 0;
	}
}

int Player::get_damage(int atk) const {
	return (atk + damage_boost) * strength;
}
