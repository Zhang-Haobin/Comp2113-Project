#include <iostream>

#include "../include/effect.h"
#include "../include/entity.h"

using namespace std;

// Apply this status effect to the generic Entity class.
// Most of the current card game uses Battle directly, but this is here for expansion.
void Effect::apply_effect_on_entity(Entity &entity) {
    switch(type) {
    case EffectType::none: { // do nothing
        break;
    }
    case EffectType::weak: {
        entity.set_strength(1 - 0.25); // constant
        break;
    }
    case EffectType::strength: {
        entity.set_damage_boost(value); // depends on value
        break;
    }
    default: {
        cout << "Unimplemented effect type!\n";
        break;
    }
    }
}
