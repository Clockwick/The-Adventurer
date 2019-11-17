
#ifndef GUJARUNSFML_ENEMY_H
#define GUJARUNSFML_ENEMY_H

#include "Entity.h"
#include "../EnemySpawner.h"

class Enemy : public Entity
{
private:
    //INITIAL
    virtual void initVariables() = 0;
    virtual void initAudio() = 0;
    virtual void initAnimation() = 0;

    //VARS
    float jumpHeight;
    bool attacking;
    bool isJump;

//    EnemySpawner& enemySpawner;

public:
    Enemy();
    virtual ~Enemy();

    //FUNCTIONS
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget& target, const bool show_hitbox = false) = 0;
    virtual void updateAnimation(const float& dt) = 0;
    virtual const bool intersects(const sf::FloatRect bounds) const = 0;

    //Attack
    virtual void gotAttackLeft() = 0;
    virtual void gotAttackRight() = 0;

    //Color
    virtual void setColor(sf::Color color);

};
#endif //GUJARUNSFML_ENEMY_H
