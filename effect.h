#ifndef EFFECT_H
#define EFFECT_H

#include "entity.h"

enum class EffectType {
    none,
    weak,
    strength,
    // todo...
};

class Effect {
public:
    EffectType type;
    int value; // associated value of the effect

    Effect();
    Effect(EffectType type, int value)
        : type(type), value(value) {}

    void apply_effect_on_entity(Entity &entity);
};

#endif // ifndef EFFECT_H
