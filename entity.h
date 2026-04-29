#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
    int max_hp;
    int hp;
    int strength = 1;                // damage multiplier
    int damage_boost = 0;            // damage boost
    int block = 0;                   // damage reduction
    // todo...
};

#endif // ifndef ENTITY_H
