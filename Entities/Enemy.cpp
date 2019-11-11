//
// Created by Paratthakorn Sribunyong on 12/11/2019 AD.
//

#include "Enemy.h"
//Constructor , DeConstructor
Enemy::Enemy(float x,  float y, const float& jumpHeight,sf::Texture& texture_sheet)
        : jumpHeight(jumpHeight)
{

    this->initVariables();
    this->initAudio();

    this->createMovementComponents(300, 1500.0f, 500.0f, this->jumpHeight);
    this->createAttributeComponents(1);
    this->createSkillComponents();
    this->createAnimationComponents( texture_sheet);
    this->initAnimation();
    this->setPosition(x , y);


Enemy::~Enemy() {


}
//Initializer Function


void Enemy::initVariables() {
    this->attacking = false;
    this->isJump = true;
}
void Enemy::initAnimation() {
    this->animationComponents->addAnimation("IDLE", 15.f, 0, 0, 3, 0, 100, 74);
    this->animationComponents->addAnimation("RUN", 15.f, 0, 1, 5, 1, 100, 74);
    this->animationComponents->addAnimation("SLIDE", 15.f, 0, 3, 3, 3, 100, 74);
    this->animationComponents->addAnimation("SIT", 15.f, 4, 0, 6, 0, 100, 74);
    this->animationComponents->addAnimation("ATTACK1", 15.f, 0, 6, 6, 6, 100, 74);
    this->animationComponents->addAnimation("ATTACK2", 15.f, 0, 7, 3, 7, 100, 74);
    this->animationComponents->addAnimation("ATTACK3", 15.f, 0, 8, 5, 8, 100 , 74);
    this->animationComponents->addAnimation("JUMP", 15.f , 0 , 2, 13 , 2 , 100 , 74);
}


void Enemy::update(const float& dt)
{
    this->movementComponents->update(dt);
    this->hitboxComponents->update();
}
void Enemy::render(sf::RenderTarget& target, const bool show_hitbox) {
    target.draw(this->sprite);

    if (show_hitbox)
        this->hitboxComponents->render(target);
}

void Enemy::initAudio() {

}
