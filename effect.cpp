#include <iostream>

#include "effect.h"
#include "entity.h"

using namespace std;

void Effect::apply_effect_on_entity(Entity &entity) {
    switch(type) {
    case EffectType::Weak: {
        entity.set_strength(1 - 0.25); // constant
        break;
    }
    case EffectType::Strength: {
        entity.set_damage_boost(value); // depends on value
        break;
    }
    default: {
        cout << "Unimplemented effect type!\n";
        break;
    }
    }
}
