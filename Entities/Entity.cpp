//
// Created by Paratthakorn Sribunyong on 2/9/2019 AD.
//

#include "Entity.h"

Entity::Entity() {
    this->shape.setSize(sf::Vector2f(50.0f,50.0f));
    this->shape.setFillColor(sf::Color::Yellow);
    this->movementSpeed = 100.0f;

}

Entity::~Entity() {

}

void Entity::move(const float& deltaTime, const float dir_x, const float dir_y) {
    this->shape.move(dir_x * this->movementSpeed * deltaTime, dir_y * this->movementSpeed * deltaTime);

}
void Entity::render(sf::RenderTarget *target) {
    target->draw(this->shape);

}
void Entity::update(const float &dt) {

}