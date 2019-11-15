
#ifndef GUJARUNSFML_SLIME_H
#define GUJARUNSFML_SLIME_H

#include "Enemy.h"

class Slime : public Enemy
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


public:
    Slime(float x, float y, const float &jumpHeight, sf::Texture &texture_sheet);
    virtual ~Slime();

    //FUNCTIONS
    void update(const float& dt);
    void render(sf::RenderTarget& target, const bool show_hitbox = false);
    void updateAnimation(const float& dt);
    void updateJumping(const float& dt);
};

#endif //GUJARUNSFML_SLIME_H
