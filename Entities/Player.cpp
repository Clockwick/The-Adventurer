//
// Created by Paratthakorn Sribunyong on 7/9/2019 AD.
//

#include "Player.h"
//Constructor , DeConstructor
Player::Player(float x,  float y,sf::Texture& texture_sheet) {

    this->initVariables();
    this->setPosition(x , y);

    this->initComponents();

    this->createHitboxComponents(this->sprite, 15.f, 5.f,20.f, 30.f);
    this->createMovementComponents(300.0f, 15.0f, 5.0f);
    this->createAnimationComponents( texture_sheet);

    this->animationComponents->addAnimation("IDLE_RIGHT", 15.f, 0, 0, 3, 0, 50, 37);
    this->animationComponents->addAnimation("RUN_RIGHT", 15.f, 1, 1, 6, 1, 50, 37);
    this->animationComponents->addAnimation("RUN_LEFT", 15.f, 1, 1, 6, 1, 50, 37);
    this->animationComponents->addAnimation("SLIDE_RIGHT", 15.f, 3, 3, 6, 3, 50, 37);


}

Player::~Player() {

}
//Initializer Function

void Player::initComponents() {
    //GIVE VALUE TO createMovementComponents
}

void Player::initVariables() {

}

void Player::update(const float& dt)
{
    this->movementComponents->update(dt);
    if (this->movementComponents->getState(IDLE))
    {
        this->animationComponents->play("IDLE_RIGHT", dt);
    }
    if (this->movementComponents->getState(SLIDE))
    {
        this->animationComponents->play("SLIDE_RIGHT", dt);
    }
    else if (this->movementComponents->getState(MOVING_RIGHT))
    {
        this->animationComponents->play("RUN_RIGHT", dt);
    }
    else if (this->movementComponents->getState(MOVING_LEFT))
    {
        this->animationComponents->play("RUN_LEFT",dt);
    }

 this->hitboxComponents->update();
}
