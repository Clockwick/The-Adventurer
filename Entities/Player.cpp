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

    this->animationComponents->addAnimation("IDLE_LEFT", 10.f, 0, 0, 7, 11, 50, 37);
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
    this->animationComponents->play("IDLE_LEFT", dt);


}
