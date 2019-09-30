//
// Created by Paratthakorn Sribunyong on 2/9/2019 AD.
//

#include "Entity.h"

void Entity::initVariables() {
    this->movementComponents = NULL;
}

Entity::Entity() {

    this->initVariables();
}

Entity::~Entity() {
    delete this->movementComponents;
    delete this->animationComponents;
}

void Entity::move(const float dir_x, const float dir_y, const float& dt) {
    if(this->movementComponents)
    {
        this->movementComponents->move(dir_x,dir_y, dt);

    }

}
void Entity::render(sf::RenderTarget *target) {
    target->draw(this->sprite);
}
void Entity::update(const float &dt) {
    if (this->movementComponents) {
        this->movementComponents->update(dt);
    }

}
//Component Functions
void Entity::setTexture(sf::Texture& texture) {
    this->sprite.setTexture(texture);

}

void Entity::setPosition(const float x, const float y) {
    this->sprite.move(x , y);

}

void Entity::createMovementComponents(const float maxVelocity, const float acceleration, const float deceleration) {

    this->movementComponents = new MovementComponents(this->sprite, maxVelocity, acceleration, deceleration);

}

void Entity::createAnimationComponents(sf::Sprite &sprite, sf::Texture &texture_sheet) {
    this->animationComponents = new AnimationComponent(sprite, texture_sheet);
}


