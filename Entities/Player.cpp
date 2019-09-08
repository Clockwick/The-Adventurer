//
// Created by Paratthakorn Sribunyong on 7/9/2019 AD.
//

#include "Player.h"
//Constructor , DeConstructor
Player::Player(float x,  float y,sf::Texture& texture) {
    this->initComponents();
    this->initVariables();
    this->setTexture(texture);
    this->setPosition(x , y);

}

Player::~Player() {

}
//Initializer Function

void Player::initComponents() {
    //GIVE VALUE TO createMovementComponents
    this->createMovementComponents(300.0f, 15.0f, 5.0f);

}

void Player::initVariables() {

}
