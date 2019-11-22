//
// Created by Paratthakorn Sribunyong on 22/11/2019 AD.
//

#ifndef GUJARUNSFML_BOSS_H
#define GUJARUNSFML_BOSS_H

#include "Enemy.h"

class Boss : public Enemy
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
Boss(float x, float y, const float &jumpHeight, sf::Texture &texture_sheet);
virtual ~Boss();

//FUNCTIONS
void update(const float& dt);
void render(sf::RenderTarget& target, const bool show_hitbox = false);
void updateAnimation(const float& dt);
void updateJumping(const float& dt);
const bool intersects(const sf::FloatRect bounds) const;
void updateMoving(const float& dt);
void updateHit();


//Got Attack
void gotAttackLeft();
void gotAttackRight();



};

#endif //GUJARUNSFML_BOSS_H
