#ifndef EFFECT_H
#define EFFECT_H

#include "entity.h"

// Left from the more general entity/effect idea.
// Battle now handles most real card effects directly.
enum class EffectType {
    none,
    weak,
    strength,
    // todo...
};

// Small effect object. It can still be useful if we expand status effects later.
class Effect {
public:
    EffectType type;
    int value; // number attached to the effect, like how much strength

    // Empty effect that does nothing.
    Effect();

    // Build an effect with a type and value.
    Effect(EffectType type, int value)
        : type(type), value(value) {}

    // Apply this effect to a generic Entity.
    void apply_effect_on_entity(Entity &entity);
};

#endif // ifndef EFFECT_H
