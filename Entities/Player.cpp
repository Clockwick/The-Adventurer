//
// Created by Paratthakorn Sribunyong on 7/9/2019 AD.
//

#include "Player.h"
//Constructor , DeConstructor
Player::Player(float x,  float y,sf::Texture& texture_sheet) {

    this->initVariables();
    this->setPosition(x , y);

    this->initComponents();

    this->createMovementComponents(300.0f, 15.0f, 5.0f);
    this->createAnimationComponents( texture_sheet);

    this->animationComponents->addAnimation("IDLE", 15.f, 0, 0, 3, 0, 50, 37);
    this->animationComponents->addAnimation("RUN", 15.f, 1, 1, 6, 1, 50, 37);
    this->animationComponents->addAnimation("SLIDE", 15.f, 3, 3, 6, 3, 50, 37);
    this->animationComponents->addAnimation("SIT", 15.f, 4, 0, 6, 0, 50, 37);
    this->animationComponents->addAnimation("ATTACK1", 15.f, 3, 6, 6, 6, 50, 37);
    this->animationComponents->addAnimation("ATTACK2", 15.f, 0, 7, 3, 7, 50, 37);

}

Player::~Player() {

}
//Initializer Function

void Player::initComponents() {
    //GIVE VALUE TO createMovementComponents
}

void Player::initVariables() {
    this->attacking = false;
    this->sliding = false;
}

void Player::update(const float& dt)
{
    this->movementComponents->update(dt);
    this->updateAttack();
    this->updateAnimation(dt);




}

void Player::updateAttack()
{
    if(this->movementComponents->getState(ATTACK))
    {
        this->attacking = true;
        //this->createHitboxComponents(this->sprite,15.f,5.f,31.f,30.f);
    }

}

void Player::updateAnimation(const float &dt)
{
    if (this->attacking)
    {

        if(this->animationComponents->play("ATTACK2", dt, true))
            this->attacking = false;

    }
    else if (this->movementComponents->getState(IDLE))
    {

        this->createHitboxComponents(this->sprite, 15.f, 5.f, 20.f, 30.f);
        this->animationComponents->play("IDLE", dt);

    }

    if (this->movementComponents->getState(SLIDE_RIGHT))
    {
        this->sliding = true;
        this->sprite.setOrigin(0.f,0.f);
        this->sprite.setScale(1.f,1.f);
        this->createHitboxComponents(this->sprite, 12.f,21.f,29.f,15.f);
        this->animationComponents->play("SLIDE", dt);
    }

    else if (this->movementComponents->getState(SLIDE_LEFT))
    {
        this->sliding = true;
        this->sprite.setOrigin(50.f,0.f);
        this->sprite.setScale(-1.f,1.f);
        this->createHitboxComponents(this->sprite, 8.f,21.f,29.f,15.f);
        this->animationComponents->play("SLIDE", dt);
    }
    else if (this->movementComponents->getState(MOVING_RIGHT))
    {


        this->sprite.setOrigin(0.f, 0.f);
        this->sprite.setScale(1.f, 1.f);
        this->createHitboxComponents(this->sprite, 17.f, 5.f, 20.f, 30.f);
        this->animationComponents->play("RUN", dt, this->movementComponents->getVelocity().x,
                                        this->movementComponents->getMaxVelocity());
    }
    else if (this->movementComponents->getState(MOVING_LEFT)) {
        this->sprite.setOrigin(50.f, 0.f);
        this->sprite.setScale(-1.f, 1.f);
        this->createHitboxComponents(this->sprite, 13.f, 5.f, 20.f, 30.f);
        this->animationComponents->play("RUN", dt, this->movementComponents->getVelocity().x,
                                        this->movementComponents->getMaxVelocity());
    }
    else if (this->movementComponents->getState(SIT))
    {
        this->createHitboxComponents(this->sprite, 15.f , 15.f, 20.f, 20.f);
        this->animationComponents->play("SIT", dt);
    }




    this->hitboxComponents->update();

}

void Player::render(sf::RenderTarget& target) {
    target.draw(this->sprite);

    if (this->hitboxComponents)
        this->hitboxComponents->render(target);
}
