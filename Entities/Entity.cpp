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
void Entity::update(const float &deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        this->move(deltaTime, -1.0f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        this->move(deltaTime, 0.0f, 1.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        this->move(deltaTime, 1.0f, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        this->move(deltaTime, 0.0f, -1.0f);
    }
}