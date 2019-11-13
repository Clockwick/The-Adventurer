
#ifndef GUJARUNSFML_ENEMY_H
#define GUJARUNSFML_ENEMY_H

#include "Entity.h"
#include "../EnemySpawner.h"

class Enemy : public Entity
{
private:
    //INITIAL
    void initVariables();
    void initAudio();
    void initAnimation();

    //VARS
    float jumpHeight;
    bool attacking;
    bool isJump;

//    EnemySpawner& enemySpawner;

public:
    Enemy( float x,  float y, const float& jumpHeight,sf::Texture& texture_sheet);
    virtual ~Enemy();

    //FUNCTIONS
    void update(const float& dt);
    void render(sf::RenderTarget& target, const bool show_hitbox = false);
    void updateAnimation(const float& dt);

};
#endif //GUJARUNSFML_ENEMY_H
