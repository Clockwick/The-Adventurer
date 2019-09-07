//
// Created by Paratthakorn Sribunyong on 7/9/2019 AD.
//

#include "Player.h"
//Constructor , DeConstructor
Player::Player(float x,  float y,sf::Texture* texture) {
    this->initComponents();
    this->initVariables();
    this->createSprite(texture);
    this->setPosition(x , y);

}

Player::~Player() {

}
//Initializer Function

void Player::initComponents() {



}

void Player::initVariables() {

}
