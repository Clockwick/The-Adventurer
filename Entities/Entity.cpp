//
// Created by Paratthakorn Sribunyong on 2/9/2019 AD.
//

#include "Entity.h"

void Entity::initVariables() {
    this->movementComponents = NULL;
    this->animationComponents = NULL;
    this->hitboxComponents = NULL;
}

Entity::Entity() {

    this->initVariables();
}

Entity::~Entity() {
    delete this->movementComponents;
    delete this->animationComponents;
    delete this->hitboxComponents;
}

void Entity::move(const float dir_x, const float dir_y, const float& dt) {
    if(this->movementComponents)
    {
        this->movementComponents->move(dir_x,dir_y, dt);

    }

}
void Entity::render(sf::RenderTarget &target) {
    target.draw(this->sprite);

    if (this->hitboxComponents)
        this->hitboxComponents->render(target);
}
void Entity::update(const float &dt) {

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

void Entity::createAnimationComponents(sf::Texture &texture_sheet) {
    this->animationComponents = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createHitboxComponents(sf::Sprite& sprite, float offset_x,
                                    float offset_y, float width, float height) {
    this->hitboxComponents = new HitboxComponents(sprite, offset_x,offset_y, width, height);
}


