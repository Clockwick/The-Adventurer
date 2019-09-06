//
// Created by Paratthakorn Sribunyong on 2/9/2019 AD.
//

#include "Entity.h"

void Entity::initVariables() {
    this->sprite = NULL;
    this->texture = NULL;
    this->movementSpeed = 100.0f;
}

Entity::Entity() {

    this->initVariables();
}

Entity::~Entity() {
    delete this->sprite;
}

void Entity::move(const float& deltaTime, const float dir_x, const float dir_y) {
    if(this->sprite)
    {
        this->sprite->move(dir_x * this->movementSpeed * deltaTime, dir_y * this->movementSpeed * deltaTime);
    }

}
void Entity::render(sf::RenderTarget *target) {
    if (this->sprite)
    {
        target->draw(*this->sprite);

    }
}
void Entity::update(const float &dt) {

}
//Component Functions
void Entity::createSprite(sf::Texture* texture) {
    this->texture = texture;
    this->sprite->setTexture(*this->texture);

}


