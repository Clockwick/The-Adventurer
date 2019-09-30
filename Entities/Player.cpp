//
// Created by Paratthakorn Sribunyong on 7/9/2019 AD.
//

#include "Player.h"
//Constructor , DeConstructor
Player::Player(float x,  float y,sf::Texture& texture_sheet) {

    this->initVariables();
    this->setTexture(texture_sheet);
    this->setPosition(x , y);

    this->initComponents();


    this->createMovementComponents(300.0f, 15.0f, 5.0f);
    this->createAnimationComponents(this->sprite, texture_sheet);

    this->animationComponents->addAnimation("IDLE_LEFT", 100.f, 0, 0, 7, 11, 50, 37);
}

Player::~Player() {

}
//Initializer Function

void Player::initComponents() {
    //GIVE VALUE TO createMovementComponents
}

void Player::initVariables() {

}
