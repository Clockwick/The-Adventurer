
#ifndef GUJARUNSFML_SLIME_H
#define GUJARUNSFML_SLIME_H

#include "Enemy.h"
#include "../Components/MovementComponent.h"

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
    bool isAttacked;
    sf::Clock delayAttackedClock;
    float delayAttackedTime;

    //Hp
    void gainHP(const int hp);
    void loseHP(const int hp);


    //Attributes
    AttributeComponent* getAttributeComponents();

    //Movement
    MovementComponents* getMovementComponents();


public:
    Slime(float x, float y, const float &jumpHeight, sf::Texture &texture_sheet);
    virtual ~Slime();

    //FUNCTIONS
    void update(const float& dt);
    void render(sf::RenderTarget& target, const bool show_hitbox = false);
    void updateAnimation(const float& dt);
    void updateJumping(const float& dt);
    const bool intersects(const sf::FloatRect bounds) const;
    void updateMoving(const float& dt);
    void updateHit();
    void dropItem();


    //Got Attack
    void gotAttackLeft();
    void gotAttackRight();



};

#endif //GUJARUNSFML_SLIME_H
